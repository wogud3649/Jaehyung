#include "CEnemy_AI_Patrol.h"
#include "Global.h"
#include "CAIController.h"
#include "Components/Characters/Enemies/CPatrolComponent.h"
#include "Components/Characters/CMontageComponent.h"
#include "Components/Characters/CInventoryComponent.h"

ACEnemy_AI_Patrol::ACEnemy_AI_Patrol()
{
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");

	CHelpers::GetAsset<UBehaviorTree>(&BehaviorTree, "BehaviorTree'/Game/Characters/Enemies/BT_Enemy_AI_Patrol.BT_Enemy_AI_Patrol'");
}

void ACEnemy_AI_Patrol::BeginPlay()
{
	Super::BeginPlay();
}

void ACEnemy_AI_Patrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACEnemy_AI_Patrol::InitBeginPlay()
{
	Status->InitName("Enemy_AI_Patrol");
}