#include "CAIController.h"
#include "Global.h"
#include "CEnemy_AI.h"
#include "Characters/CCharacter.h"
#include "Characters/Turrets/CTurret.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/Characters/Enemies/CBehaviorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Objects/CBreakable.h"

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(NULL, actors);

	AActor* target = NULL;

	for (AActor* actor : actors)
	{
		target = Cast<ACCharacter>(actor);
		if (target)
		{
			if (Cast<ACCharacter>(target)->GetTeamID() != Cast<ACCharacter>(GetPawn())->GetTeamID())
			{
				break;
			}
		}

		target = Cast<ACBreakable>(actor);
		if (target)
		{
			break;
		}
	}

	Blackboard->SetValueAsObject("Target", target);
}

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");
	CHelpers::CreateActorComponent<UCBehaviorComponent>(this, &Behavior, "Behavior");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 600;
	Sight->LoseSightRadius = 800;
	Sight->PeripheralVisionAngleDegrees = 90;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bDrawDebug);

	FVector center = Pawn->GetActorLocation();
	center.Z -= AdjustCircleHeight;
	DrawDebugCircle(GetWorld(), center, Sight->SightRadius, 300, FColor::Green, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector);
	DrawDebugCircle(GetWorld(), center, ActionRange, 300, FColor::Red, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector);
}

void ACAIController::SetActionRange(float InActionRange)
{
	ActionRange = InActionRange;

	if (ActionRange > 200)
	{
		Sight->SightRadius = ActionRange + 200;
		Sight->LoseSightRadius = ActionRange + 400;

		Perception->ConfigureSense(*Sight);
		Perception->SetDominantSense(*Sight->GetSenseImplementation());
	}
}

float ACAIController::GetSightRadius()
{
	return Sight->SightRadius;
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Pawn = Cast<ACCharacter>(InPawn);
	SetGenericTeamId(Pawn->GetTeamID());

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);

	UBehaviorTree* behaviorTree = NULL;
	ACEnemy_AI* enemy_AI = Cast<ACEnemy_AI>(Pawn);
	if (enemy_AI)
		behaviorTree = enemy_AI->GetBehaviorTree();

	ACTurret* turret = Cast<ACTurret>(Pawn);
	if (turret)
		behaviorTree = turret->GetBehaviorTree();

	if (!behaviorTree)
	{
		CLog::Print("NoBehaviorTree");
		return;
	}

	UseBlackboard(behaviorTree->BlackboardAsset, Blackboard);
	Behavior->SetBlackboard(Blackboard);

	RunBehaviorTree(behaviorTree);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}