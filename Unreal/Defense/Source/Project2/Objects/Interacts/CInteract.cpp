#include "CInteract.h"
#include "Global.h"
#include "Components/Utilities/CInteractComponent.h"

void ACInteract::OnInteract(AActor* InActor)
{
	if (GetOwner())
		return;

	BeginInteract(InActor);
}

void ACInteract::OffInteract(AActor* InActor)
{
	if (GetOwner())
		return;

	EndInteract(InActor);
}

ACInteract::ACInteract()
{
	CHelpers::CreateActorComponent<UCInteractComponent>(this, &Interact, "Interact");
}

void ACInteract::BeginPlay()
{
	Super::BeginPlay();

	Interact->OnInteract.AddDynamic(this, &ACInteract::OnInteract);
	Interact->OffInteract.AddDynamic(this, &ACInteract::OffInteract);
}

void ACInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}