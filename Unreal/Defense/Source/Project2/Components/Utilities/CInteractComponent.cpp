#include "CInteractComponent.h"
#include "Global.h"

UCInteractComponent::UCInteractComponent()
{
}

void UCInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCInteractComponent::ChangeType(EInteractType InType)
{
	Type = InType;
}

void UCInteractComponent::BeginInteract(AActor* InActor)
{
	switch (Type)
	{
	case EInteractType::Hold:
		Interact(InActor, true);
		break;
	case EInteractType::Toggle:
		if (bInteract)
			Interact(InActor, false);
		else
			Interact(InActor, true);
		break;
	}
}

void UCInteractComponent::EndInteract(AActor* InActor)
{
	switch (Type)
	{
	case EInteractType::Hold:
		Interact(InActor, false);
		break;
	case EInteractType::Toggle:
		break;
	}
}

void UCInteractComponent::Interact(AActor* InActor, bool bInInteract)
{
	Actor = InActor;
	bInteract = bInInteract;

	if (bInteract)
	{
		if (OnInteract.IsBound())
			OnInteract.Broadcast(Actor);
	}
	else
	{
		if (OffInteract.IsBound())
			OffInteract.Broadcast(Actor);
	}
}