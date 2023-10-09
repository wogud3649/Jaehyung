#include "CEnemy_AI.h"
#include "Global.h"
#include "CAIController.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Characters/CMontageComponent.h"
#include "Objects/Interacts/Holds/Items/Weapons/OneHands/CSword.h"

ACEnemy_AI::ACEnemy_AI()
{
	AIControllerClass = ACAIController::StaticClass();

	Inventory->ClearMoney();
	Inventory->AddMoney(100);

	CHelpers::GetAsset<UBehaviorTree>(&BehaviorTree, "BehaviorTree'/Game/Characters/Enemies/BT_Enemy_AI.BT_Enemy_AI'");

	AutoPossessAI = EAutoPossessAI::Spawned;
}

void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();
}

void ACEnemy_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACEnemy_AI::InitBeginPlay()
{
	Status->InitName("Enemy_AI");
}