#include "CToggle_BasicShape.h"
#include "Global.h"
#include "Components/Objects/CBasicShapeComponent.h"

ACToggle_BasicShape::ACToggle_BasicShape()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);

	CHelpers::CreateActorComponent<UCBasicShapeComponent>(this, &BasicShape, "BasicShape");
	BasicShape->InitShape(Mesh);
}

void ACToggle_BasicShape::BeginPlay()
{
	Super::BeginPlay();
}

void ACToggle_BasicShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACToggle_BasicShape::BeginInteract(AActor* InActor)
{
	BasicShape->BeginInteract(InActor);
}

void ACToggle_BasicShape::EndInteract(AActor* InActor)
{
	BasicShape->EndInteract();
}