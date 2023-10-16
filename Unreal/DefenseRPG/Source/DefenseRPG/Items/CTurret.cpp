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

	if (bFollowCursor)
	{
		FHitResult hitResult;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);

		if (hitResult.bBlockingHit)
		{
			SetActorLocation(hitResult.ImpactPoint);
		}
	}
}

void ACTurret::Rooted()
{
	bFollowCursor = true;
	SetCollisionEnabled(false);
}

void ACTurret::OnSelected()
{
	SetActorHiddenInGame(false);
}

void ACTurret::OffSelected()
{
	SetActorHiddenInGame(true);
}

void ACTurret::Dumped()
{
	bFollowCursor = false;
	SetCollisionEnabled(true);
}

void ACTurret::SetCollisionEnabled(bool bCollisionEnable)
{
	if (bCollisionEnable)
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}