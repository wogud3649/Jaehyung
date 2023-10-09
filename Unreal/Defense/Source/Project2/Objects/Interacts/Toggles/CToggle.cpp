#include "CToggle.h"
#include "Global.h"
#include "Components/Utilities/CInteractComponent.h"

ACToggle::ACToggle()
{
	Interact->SetToggle();
}

void ACToggle::BeginPlay()
{
	Super::BeginPlay();
}

void ACToggle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}