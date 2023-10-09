#include "CBasicShapeComponent.h"
#include "Global.h"
#include "Camera/CameraComponent.h"

UCBasicShapeComponent::UCBasicShapeComponent()
{
}

void UCBasicShapeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCBasicShapeComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FProperty* p = PropertyChangedEvent.Property;
	CheckNull(p);

	if (p->GetName() == "Type")
		ChangeShape();
}

void UCBasicShapeComponent::InitShape(UStaticMeshComponent* InMesh)
{
	FString path = GetPath();

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, path);
	InMesh->SetStaticMesh(mesh);
	InMesh->SetCollisionProfileName("Custom");
	InMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	InMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InMesh->bCastDynamicShadow = false;
}

void UCBasicShapeComponent::BeginInteract(AActor* InActor)
{
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(InActor);
	CheckNull(camera);

	GetOwner()->AttachToComponent(camera, FAttachmentTransformRules::KeepWorldTransform);
}

void UCBasicShapeComponent::EndInteract()
{
	GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

FString UCBasicShapeComponent::GetPath()
{
	FString path = "StaticMesh'/Game/Resources/Mesh/BasicShapes/";

	switch (Type)
	{
	case EBasicShapeType::Cube:
		path += "Cube.Cube'";
		break;
	case EBasicShapeType::Cone:
		path += "Cone.Cone'";
		break;
	case EBasicShapeType::Cylinder:
		path += "Cylinder.Cylinder'";
		break;
	case EBasicShapeType::Plane:
		path += "Plane.Plane'";
		break;
	case EBasicShapeType::Sphere:
		path += "Sphere.Sphere'";
		break;
	case EBasicShapeType::Max:
		Type = OldType;
		path = GetPath();
		break;
	}

	return path;
}

void UCBasicShapeComponent::ChangeShape()
{
	UStaticMeshComponent* component = CHelpers::GetComponent<UStaticMeshComponent>(GetOwner());
	CheckNull(component);

	FString path = GetPath();

	UStaticMesh* mesh;
	CHelpers::GetAssetDynamic<UStaticMesh>(&mesh, path);
	component->SetStaticMesh(mesh);

	OldType = Type;
}