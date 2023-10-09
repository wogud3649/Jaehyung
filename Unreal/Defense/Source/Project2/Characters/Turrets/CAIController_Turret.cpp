#include "CAIController_Turret.h"
#include "Global.h"
#include "CTurret.h"
#include "Characters/Enemies/CEnemy.h"
#include "Characters/CCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/Characters/Enemies/CBehaviorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Objects/CBreakable.h"

void ACAIController_Turret::OnPerceptionUpdated(const TArray<AActor*>& UpdateActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), actors);

	AActor* target = NULL;

	for (AActor* actor : actors)
	{
		target = Cast<ACEnemy>(actor);
		if (target)
		{
			break;
		}
	}

	Blackboard->SetValueAsObject("Target", target);
}

ACAIController_Turret::ACAIController_Turret()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");
	CHelpers::CreateActorComponent<UCBehaviorComponent>(this, &Behavior, "Behavior");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 250;
	Sight->LoseSightRadius = 450;
	Sight->PeripheralVisionAngleDegrees = 90;
	Sight->SetMaxAge(2);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void ACAIController_Turret::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bDrawDebug);

	FVector center = Pawn->GetActorLocation();
	center.Z -= AdjustCircleHeight;
	DrawDebugCircle(GetWorld(), center, Sight->SightRadius, 300, FColor::Green, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector);
	DrawDebugCircle(GetWorld(), center, ActionRange, 300, FColor::Red, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector);
}

void ACAIController_Turret::SetActionRange(float InActionRange)
{
	ActionRange = InActionRange;

	if (ActionRange > 150)
	{
		Sight->SightRadius = ActionRange + 100;
		Sight->LoseSightRadius = ActionRange + 300;

		Perception->ConfigureSense(*Sight);
		Perception->SetDominantSense(*Sight->GetSenseImplementation());
	}
}

float ACAIController_Turret::GetSightRadius()
{
	return Sight->SightRadius;
}

void ACAIController_Turret::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Pawn = Cast<ACCharacter>(InPawn);
	SetGenericTeamId(Pawn->GetTeamID());

	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController_Turret::OnPerceptionUpdated);

	UBehaviorTree* behaviorTree = NULL;
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

void ACAIController_Turret::OnUnPossess()
{
	Super::OnUnPossess();

	Perception->OnPerceptionUpdated.Clear();
}