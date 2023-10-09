#include "COneHand.h"
#include "Global.h"
#include "Components/Objects/CItemComponent.h"

ACOneHand::ACOneHand()
{
	Item->SetType(EItemType::OneHand);
}

void ACOneHand::BeginPlay()
{
	Super::BeginPlay();
}

void ACOneHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}