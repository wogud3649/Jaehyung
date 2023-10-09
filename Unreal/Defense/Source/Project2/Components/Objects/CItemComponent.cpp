#include "CItemComponent.h"
#include "Global.h"
#include "Components/Utilities/CTraceComponent.h"

UCItemComponent::UCItemComponent()
{
}

void UCItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCItemComponent::OnRoot(AActor* InActor)
{
	CheckTrue(bRooted);

	if (OnItemRoot.IsBound())
		OnItemRoot.Broadcast(InActor);

	bRooted = true;

	UCTraceComponent* trace = CHelpers::GetComponent<UCTraceComponent>(InActor);
	CheckNull(trace);

	trace->SetActorToIgnore(GetOwner());
}

void UCItemComponent::OffRoot(AActor* InActor)
{
	CheckFalse(bRooted);

	if (OffItemRoot.IsBound())
		OffItemRoot.Broadcast(InActor);

	bRooted = false;

	UCTraceComponent* trace = CHelpers::GetComponent<UCTraceComponent>(InActor);
	CheckNull(trace);

	trace->RemoveActorToIgnore(GetOwner());
}

void UCItemComponent::BeginAction(bool bLeft)
{
	if (OnAction.IsBound())
		OnAction.Broadcast(bLeft);
}

void UCItemComponent::EndAction(bool bLeft)
{
	if (OffAction.IsBound())
		OffAction.Broadcast(bLeft);
}

void UCItemComponent::ChangeType(EItemType InType)
{
	Type = InType;
}