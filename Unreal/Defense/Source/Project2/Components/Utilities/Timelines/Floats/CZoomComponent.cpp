#include "CZoomComponent.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"

void UCZoomComponent::Zoom(float Output)
{
	SpringArm->TargetArmLength = Output;
}

UCZoomComponent::UCZoomComponent()
{
}

void UCZoomComponent::BeginPlay()
{
	Super::BeginPlay();

	CurveFloat.AddDynamic(this, &UCZoomComponent::Zoom);
}