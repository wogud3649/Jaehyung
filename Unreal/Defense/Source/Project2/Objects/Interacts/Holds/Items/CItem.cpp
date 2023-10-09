#include "CItem.h"
#include "Global.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Objects/CItemComponent.h"

void ACItem::OnRoot(AActor* InActor)
{
	BeginRoot(InActor);
}

void ACItem::OffRoot(AActor* InActor)
{
	EndRoot(InActor);
}

void ACItem::OnAction(bool bLeft)
{
	BeginAction(bLeft);
}

void ACItem::OffAction(bool bLeft)
{
	EndAction(bLeft);
}

ACItem::ACItem()
{
	CHelpers::CreateActorComponent<UCItemComponent>(this, &Item, "Item");
}

void ACItem::BeginPlay()
{
	Super::BeginPlay();

	Item->OnItemRoot.AddDynamic(this, &ACItem::OnRoot);
	Item->OffItemRoot.AddDynamic(this, &ACItem::OffRoot);
	Item->OnAction.AddDynamic(this, &ACItem::OnAction);
	Item->OffAction.AddDynamic(this, &ACItem::OffAction);
}

void ACItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACItem::BeginInteract(AActor* InActor)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(InActor);
	CheckNull(inventory);

	inventory->Root(this);
}

void ACItem::EndInteract(AActor* InActor)
{
}