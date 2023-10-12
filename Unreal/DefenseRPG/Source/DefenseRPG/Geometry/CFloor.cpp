#include "CFloor.h"
#include "Global.h"

ACFloor::ACFloor()
{
	SetMesh("StaticMesh'/Game/Resources/Geometry/Meshes/Floor.Floor'");
}

void ACFloor::BeginPlay()
{
	Super::BeginPlay();
}

void ACFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}