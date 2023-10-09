#include "CStatusComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Objects/CWeaponComponent.h"

UCStatusComponent::UCStatusComponent()
{
}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCStatusComponent::InitName(FString InName)
{
	FString name = InName;

	TArray<UWidgetComponent*> widgets;
	GetOwner()->GetComponents(widgets);

	for (int32 i = 0; i < widgets.Num(); i++)
	{
		UCUW_Name* nameWidget = Cast<UCUW_Name>(widgets[i]->GetUserWidgetObject());
		if (nameWidget)
		{
			Name = nameWidget;
			break;
		}
	}

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwner());
	if (inventory)
	{
		if (inventory->GetSelectedItem())
		{
			UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(inventory->GetSelectedItem());
			if (weapon)
			{
				switch (weapon->GetType())
				{
				case EWeaponType::Sword:
					name += "_Sword";
					break;
				case EWeaponType::GreatSword:
					name += "_GreatSword";
					break;
				case EWeaponType::Pistol:
					name += "_Pistol";
					break;
				}
			}
		}
	}

	Name->SetNameText(name);
}

void UCStatusComponent::InitHealth()
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

void UCStatusComponent::AddHealth(float InAmount)
{
	CheckFalse(bDead);

	Health += InAmount;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	UpdateHealth();
}

void UCStatusComponent::SubHealth(float InAmount, ACharacter* InCauser)
{
	CheckTrue(bDead);

	Health -= InAmount;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	if (Health > 0)
	{
		ChangeType(EStatusType::Hitted);
	}
	else
	{
		bDead = true;
		ChangeType(EStatusType::Dead);

		APawn* pawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
		if (pawn)
		{
			UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(pawn);
			if (inventory)
			{
				UCInventoryComponent* ownerInventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwner());
				if (ownerInventory)
				{
					inventory->AddMoney(ownerInventory->GetMoney());
					ownerInventory->ClearMoney();
				}
			}
		}
	}

	UpdateHealth();
}

void UCStatusComponent::UpdateHealth()
{
	CheckNull(HealthBar);

	HealthBar->Update(Health, MaxHealth);
}

void UCStatusComponent::ChangeType(EStatusType InType)
{
	Type = InType;

	if (OnStatusChanged.IsBound())
		OnStatusChanged.Broadcast(Type);
}