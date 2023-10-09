#include "CHold.h"
#include "Global.h"
#include "Components/Utilities/CInteractComponent.h"

ACHold::ACHold()
{
	Interact->SetHold();
}

void ACHold::BeginPlay()
{
	Super::BeginPlay();
}

void ACHold::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}