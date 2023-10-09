#include "CItem_BasicShape.h"
#include "Global.h"
#include "Components/Objects/CBasicShapeComponent.h"
#include "Components/Objects/CItemComponent.h"
#include "Components/Characters/CInventoryComponent.h"

ACItem_BasicShape::ACItem_BasicShape()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);

	CHelpers::CreateActorComponent<UCBasicShapeComponent>(this, &BasicShape, "BasicShape");

	Mesh->SetCollisionProfileName("Custom");
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);

	BasicShape->InitShape(Mesh);

	Item->SetType(EItemType::Box);
}

void ACItem_BasicShape::BeginPlay()
{
	Super::BeginPlay();
}

void ACItem_BasicShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACItem_BasicShape::BeginInteract(AActor* InActor)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(InActor);
	CheckNull(inventory);

	inventory->Root(this);
}

void ACItem_BasicShape::EndInteract(AActor* InActor)
{
}

void ACItem_BasicShape::BeginRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	AttachToComponent_Relative(Mesh, mesh, "Item_BasicShape", true);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACItem_BasicShape::EndRoot(AActor* InActor)
{
	UMeshComponent* mesh = CHelpers::GetComponent<UMeshComponent>(InActor);
	CheckNull(mesh);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	DetachFromComponent(Mesh, mesh, FDetachmentTransformRules::KeepWorldTransform, true);
}