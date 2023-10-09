#include "CPortal.h"
#include "Global.h"
#include "Components/Objects/CBasicShapeComponent.h"
#include "Components/Objects/CPortalComponent.h"

ACPortal::ACPortal()
{
	CHelpers::CreateActorComponent<UCPortalComponent>(this, &Portal, "Portal");

	BasicShape->SetType(EBasicShapeType::Cylinder);

	UMaterialInterface* material;
	CHelpers::GetAsset<UMaterialInterface>(&material, "Material'/Game/Resources/Materials/Expendables/Shells/M_Plasma_Shot_Shell.M_Plasma_Shot_Shell'");
	Mesh->SetMaterial(0, material);
	Mesh->SetRelativeRotation(FRotator(90, 0, 0));
	Mesh->SetRelativeScale3D(FVector(3, 3, 0.01f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACPortal::BeginPlay()
{
	Super::BeginPlay();
}

void ACPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}