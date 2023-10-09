#include "CInventoryComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Characters/Turrets/CTurret.h"
#include "Components/Objects/CItemComponent.h"
#include "Components/Objects/CGunComponent.h"
#include "Components/Utilities/CInteractComponent.h"

UCInventoryComponent::UCInventoryComponent()
{
	Inventory.SetNum(Size);
}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bPlayer)
	{
		InventoryWidget = CreateWidget<UCUW_Inventory, APlayerController>(Cast<ACharacter>(GetOwner())->GetController<APlayerController>(), InventoryWidgetClass);
		InventoryWidget->AddToViewport();
	}

	UpdateSelected();
}

void UCInventoryComponent::SetPlayer()
{
	bPlayer = true;

	CHelpers::GetClass<UCUW_Inventory>(&InventoryWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Inventory.BP_CUW_Inventory_C'");
}

void UCInventoryComponent::Root(AActor* InActor)
{
	for (AActor* item : Inventory)
	{
		CheckTrue(item == InActor);
	}

	for (int32 i = 0; i < Size; i++)
	{
		if (!Inventory[i])
		{
			UCItemComponent* item = CHelpers::GetComponent<UCItemComponent>(InActor);
			if (item)
			{
				InActor->SetOwner(GetOwner());
				Inventory[i] = InActor;

				if (InventoryWidget)
				{
					InventoryWidget->SetItem((int32)item->GetType(), i);
				}

				item->OnRoot(GetOwner());

				UpdateSelected();

				if (Selected != i)
				{
					InActor->SetActorHiddenInGame(true);
					InventoryWidget->OffSelect(i);

					ACTurret* turret = Cast<ACTurret>(InActor);
					if (turret)
						turret->EndSelected();
				}
				break;
			}
		}
	}
}

void UCInventoryComponent::Dump()
{
	CheckNull(Inventory[Selected]);

	UCItemComponent* item = CHelpers::GetComponent<UCItemComponent>(Inventory[Selected]);
	CheckNull(item);

	item->OffRoot(GetOwner());
	Inventory[Selected]->SetOwner(nullptr);
	Inventory[Selected] = nullptr;

	if (InventoryWidget)
	{
		InventoryWidget->SetItem(0, Selected);
	}

	UpdateSelected();
}

void UCInventoryComponent::DumpAll()
{
	for (int32 i = 0; i < Size; i++)
	{
		if (!Inventory[i])
			continue;

		UCItemComponent* item = CHelpers::GetComponent<UCItemComponent>(Inventory[i]);
		if (!item)
			continue;

		item->OffRoot(GetOwner());
		Inventory[i]->SetActorHiddenInGame(false);
		Inventory[i]->SetOwner(nullptr);
		Inventory[i] = nullptr;

		if (!InventoryWidget)
			continue;
		InventoryWidget->SetItem(0, i);
		InventoryWidget->OffSelect(OldSelected);
	}
}

void UCInventoryComponent::DestroyAll()
{
	for (int32 i = 0; i < Size; i++)
	{
		if (!Inventory[i])
			continue;

		Inventory[i]->Destroy();
	}
}

void UCInventoryComponent::Select(int32 index)
{
	Selected = index;

	if (Selected >= Size)
		Selected = Size - 1;
	else if (Selected < 0)
		Selected = 0;

	UpdateSelected();
}

void UCInventoryComponent::Right()
{
	Selected++;

	if (Selected >= Size)
		Selected = 0;

	UpdateSelected();
}

void UCInventoryComponent::Left()
{
	Selected--;

	if (Selected < 0)
		Selected = Size - 1;

	UpdateSelected();
}

void UCInventoryComponent::BeginAction(bool bLeft)
{
	AActor* actor = Inventory[Selected];
	CheckNull(actor);

	UCItemComponent* item = CHelpers::GetComponent<UCItemComponent>(actor);
	CheckNull(item);

	item->BeginAction(bLeft);
}

void UCInventoryComponent::EndAction(bool bLeft)
{
	CheckNull(Inventory[Selected]);

	UCItemComponent* item = CHelpers::GetComponent<UCItemComponent>(Inventory[Selected]);
	CheckNull(item);

	item->EndAction(bLeft);
}

void UCInventoryComponent::Reload()
{
	CheckNull(Inventory[Selected]);

	UCGunComponent* gun = CHelpers::GetComponent<UCGunComponent>(Inventory[Selected]);
	CheckNull(gun);

	gun->Reload();
}

void UCInventoryComponent::UpdateSelected()
{
	if (Selected == OldSelected)
	{
		if (InventoryWidget)
		{
			InventoryWidget->OnSelect(Selected);
		}
	}
	else
	{
		if (InventoryWidget)
		{
			InventoryWidget->OnSelect(Selected);
			InventoryWidget->OffSelect(OldSelected);
		}

		if (Inventory[Selected])
		{
			Inventory[Selected]->SetActorHiddenInGame(false);

			ACTurret* turret = Cast<ACTurret>(Inventory[Selected]);
			if (turret)
				turret->BeginSelected();
		}
		if (Inventory[OldSelected])
		{
			Inventory[OldSelected]->SetActorHiddenInGame(true);

			ACTurret* turret = Cast<ACTurret>(Inventory[OldSelected]);
			if (turret)
				turret->EndSelected();
		}

		OldSelected = Selected;
	}

	if (SelectedItem.IsBound())
		SelectedItem.Broadcast(Inventory[Selected]);
}

void UCInventoryComponent::AddMoney(float InAmount)
{
	Money += InAmount;

	if(InventoryWidget)
		InventoryWidget->UpdateMoney(Money);
}

bool UCInventoryComponent::SubMoney(float InAmount)
{
	if (Money < InAmount)
		return false;

	Money -= InAmount;

	if (InventoryWidget)
		InventoryWidget->UpdateMoney(Money);

	return true;
}