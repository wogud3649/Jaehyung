#include "CTurret.h"
#include "Global.h"
#include "Components/Items/CItemComponent.h"

ACTurret::ACTurret()
{
	// CreateComponent
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);

	// Mesh
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Resources/Items/Turrets/Meshes/Turret.Turret'");
	if (mesh)
		Mesh->SetStaticMesh(mesh);

	// Item
	Item->SetItemCode(1);
}

void ACTurret::BeginPlay()
{
	Super::BeginPlay();
}

void ACTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}