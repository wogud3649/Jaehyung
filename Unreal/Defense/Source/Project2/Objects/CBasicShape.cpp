#include "CBasicShape.h"
#include "Global.h"
#include "Components/Objects/CBasicShapeComponent.h"

ACBasicShape::ACBasicShape()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);

	CHelpers::CreateActorComponent<UCBasicShapeComponent>(this, &BasicShape, "BasicShape");

	BasicShape->InitShape(Mesh);
}

void ACBasicShape::BeginPlay()
{
	Super::BeginPlay();
}

void ACBasicShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}