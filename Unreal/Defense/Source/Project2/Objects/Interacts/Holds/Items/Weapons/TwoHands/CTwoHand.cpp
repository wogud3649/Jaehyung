#include "CTwoHand.h"
#include "Global.h"
#include "Components/Objects/CItemComponent.h"

ACTwoHand::ACTwoHand()
{
	Item->SetType(EItemType::TwoHand);
}

void ACTwoHand::BeginPlay()
{
	Super::BeginPlay();
}

void ACTwoHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}