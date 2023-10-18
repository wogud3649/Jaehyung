#include "CItem.h"
#include "Global.h"
#include "Components/Items/CItemComponent.h"

ACItem::ACItem()
{
	// CreateComponent
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");

	// CreateActorComponent
	CHelpers::CreateActorComponent<UCItemComponent>(this, &Item, "Item");

	// Tick
	PrimaryActorTick.bCanEverTick = true;
}

void ACItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACItem::Rooted()
{
}

void ACItem::OnSelected()
{
}

void ACItem::OffSelected()
{
}

void ACItem::Dumped()
{
}

bool ACItem::PlayAction(bool bLeftClick)
{
	return false;
}

void ACItem::SetCollisionEnabled(bool bCollisionEnable)
{
}