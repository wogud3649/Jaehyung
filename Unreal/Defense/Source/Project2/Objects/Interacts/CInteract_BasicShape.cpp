#include "CInteract_BasicShape.h"
#include "Global.h"
#include "Components/Objects/CBasicShapeComponent.h"

ACInteract_BasicShape::ACInteract_BasicShape()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	CHelpers::CreateActorComponent<UCBasicShapeComponent>(this, &BasicShape, "BasicShape");

	BasicShape->InitShape(Mesh);
}

void ACInteract_BasicShape::BeginPlay()
{
	Super::BeginPlay();
}

void ACInteract_BasicShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}