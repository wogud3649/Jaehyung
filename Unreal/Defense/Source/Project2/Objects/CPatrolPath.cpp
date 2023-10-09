#include "CPatrolPath.h"
#include "Global.h"

ACPatrolPath::ACPatrolPath()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<USplineComponent>(this, &Spline, "Spline", Scene);
}

void ACPatrolPath::BeginPlay()
{
	Super::BeginPlay();
}