#include "CPortalComponent.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy_AI_Patrol.h"
#include "Components/Characters/Enemies/CPatrolComponent.h"
#include "Objects/CPatrolPath.h"

UCPortalComponent::UCPortalComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCPortalComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCPortalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Duration += DeltaTime;

	if (Duration > SpawnInterval)
	{
		Duration = 0;

		Spawn();
	}
}

void UCPortalComponent::Spawn()
{
	CheckNull(GetOwner());

	FTransform transform;
	transform.SetLocation(GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 200);
	transform.SetRotation(FQuat(GetOwner()->GetActorForwardVector().Rotation()));

	ACEnemy_AI_Patrol* patrol = GetWorld()->SpawnActorDeferred<ACEnemy_AI_Patrol>(ACEnemy_AI_Patrol::StaticClass(), transform, GetOwner());
	if (patrol)
	{
		UGameplayStatics::FinishSpawningActor(patrol, transform);
		patrol->SetWeapon((EWeaponType)(UKismetMathLibrary::RandomInteger((int32)EWeaponType::Max - 1) + 1));

		UCPatrolComponent* patrolComponent = CHelpers::GetComponent<UCPatrolComponent>(patrol);
		if (patrolComponent)
		{
			ACPatrolPath* patrolPath = Cast<ACPatrolPath>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPatrolPath::StaticClass()));
			if (patrolPath)
			{
				patrolComponent->SetPatrolPath(patrolPath);
			}
		}
	}

	if (bDrawDebug)
		DrawDebugSphere(GetWorld(), transform.GetLocation(), 100, 100, FColor::Green, false, 1.0f);
}