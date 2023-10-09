#include "CHold_BasicShape.h"
#include "Global.h"
#include "Components/Objects/CBasicShapeComponent.h"

ACHold_BasicShape::ACHold_BasicShape()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);

	CHelpers::CreateActorComponent<UCBasicShapeComponent>(this, &BasicShape, "BasicShape");

	BasicShape->InitShape(Mesh);
}

void ACHold_BasicShape::BeginPlay()
{
	Super::BeginPlay();
}

void ACHold_BasicShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACHold_BasicShape::BeginInteract(AActor* InActor)
{
	BasicShape->BeginInteract(InActor);
}

void ACHold_BasicShape::EndInteract(AActor* InActor)
{
	BasicShape->EndInteract();
}