#include "CBreakableComponent.h"
#include "Global.h"
#include "Components/WidgetComponent.h"
#include "Components/Widgets/CResultComponent.h"
#include "Widgets/CUW_Health.h"

UCBreakableComponent::UCBreakableComponent()
{
	MeshAssets.Empty();

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Resources/Mesh/Objects/Breakables/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1'");
	MeshAssets.Add(mesh);

	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Resources/Mesh/Objects/Breakables/SM_Env_Breakables_BoxesBITS.SM_Env_Breakables_BoxesBITS'");
	MeshAssets.Add(mesh);
}

void UCBreakableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCBreakableComponent::TickBreakable(float DeltaTime)
{
	if (bChanged)
	{
		UpdateMesh();
	}

	if (bDestroyed)
	{
		DestroyDelay -= DeltaTime;

		if (DestroyDelay < 0)
		{
			UCResultComponent* result = CHelpers::GetComponent<UCResultComponent>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
			if (result)
				result->Lose();
			GetOwner()->K2_DestroyActor();
		}
	}
}

void UCBreakableComponent::InitHealth()
{
	TArray<UWidgetComponent*> widgets;
	GetOwner()->GetComponents(widgets);

	for (int32 i = 0; i < widgets.Num(); i++)
	{
		UCUW_Health* health = Cast<UCUW_Health>(widgets[i]->GetUserWidgetObject());
		if (health)
		{
			HealthBar = health;
			break;
		}
	}

	Health = MaxHealth;

	UpdateHealth();
}

void UCBreakableComponent::AddHealth(float InAmount)
{
	CheckFalse(bDestroyed);

	Health += InAmount;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	UpdateHealth();
}

void UCBreakableComponent::SubHealth(float InAmount)
{
	CheckTrue(bDestroyed);

	Health -= InAmount;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	UpdateHealth();
}

void UCBreakableComponent::UpdateHealth()
{
	CheckNull(HealthBar);

	HealthBar->Update(Health, MaxHealth);

	int32 num = MeshAssets.Num();
	CheckFalse(num > 1);

	for (int32 i = 0; i < num; i++)
	{
		int32 changeHealth = MaxHealth;
		changeHealth -= MaxHealth / num * (i + 1);
		if (Health <= changeHealth)
		{
			Selected = i;
			bChanged = true;
		}
		else
		{
			break;
		}
	}

	if (Health <= 0)
	{
		Health = 0;
		bDestroyed = true;
	}
}

void UCBreakableComponent::UpdateMesh()
{
	bChanged = false;
	UStaticMeshComponent* mesh = CHelpers::GetComponent<UStaticMeshComponent>(GetOwner());
	CheckNull(mesh);

	UStaticMesh* staticMesh = MeshAssets[Selected];
	CheckNull(staticMesh);

	mesh->SetStaticMesh(staticMesh);
}