#include "CTurret.h"
#include "Global.h"
#include "Components/Items/CItemComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

void ACTurret::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bPlanted)
	{

	}
	else
	{
		if (IndicatorDynamicMaterial)
		{
			IndicatorDynamicMaterial->SetVectorParameterValue("BodyColor", IndicatorOverlapedColor);
			bPlantable = false;
		}
	}
}

void ACTurret::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bPlanted)
	{

	}
	else
	{
		if (IndicatorDynamicMaterial)
		{
			IndicatorDynamicMaterial->SetVectorParameterValue("BodyColor", IndicatorBaseColor);
			bPlantable = true;
		}
	}
}

ACTurret::ACTurret()
{
	// CreateComponent
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Scene);
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Mesh);

	// Mesh
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Resources/Items/Turrets/Meshes/Turret.Turret'");
	if (mesh)
		Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeLocation(FVector(0, 0, 50));
	SetCollisionEnabled(false);

	CHelpers::GetAsset<UMaterialInterface>(&Material, "MaterialInstanceConstant'/Game/Resources/Items/Turrets/Materials/M_Turret_Inst.M_Turret_Inst'");
	CHelpers::GetAsset<UMaterialInterface>(&IndicatorMaterial, "MaterialInstanceConstant'/Game/Resources/Items/Turrets/Materials/M_Indicator_Inst.M_Indicator_Inst'");

	// Box
	Box->SetRelativeScale3D(FVector(2, 2, 1));
	Box->SetHiddenInGame(false);

	// Item
	Item->SetItemCode(1);
}

void ACTurret::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACTurret::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACTurret::OnComponentEndOverlap);
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
	if (!DynamicMaterial)
	{
		UMaterialInstanceConstant* constantMaterial = Cast<UMaterialInstanceConstant>(Material);
		DynamicMaterial = UMaterialInstanceDynamic::Create(constantMaterial, this);
	}

	if (!IndicatorDynamicMaterial)
	{
		UMaterialInstanceConstant* constantMaterial = Cast<UMaterialInstanceConstant>(IndicatorMaterial);
		IndicatorDynamicMaterial = UMaterialInstanceDynamic::Create(constantMaterial, this);
	}

	bFollowCursor = true;
	bPlanted = false;

	Mesh->SetMaterial(0, IndicatorDynamicMaterial);
}

void ACTurret::OnSelected()
{
	SetActorHiddenInGame(false);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACTurret::OffSelected()
{
	SetActorHiddenInGame(true);
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACTurret::Dumped()
{
	bFollowCursor = false;
	bPlanted = true;

	Mesh->SetMaterial(0, DynamicMaterial);
}

bool ACTurret::PlayAction(bool bLeftClick)
{
	if (bLeftClick)
	{
		if (bPlantable)
		{
			Dumped();

			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{

	}

	return false;
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