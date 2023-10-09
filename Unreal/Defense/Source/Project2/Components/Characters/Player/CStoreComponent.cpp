#include "CStoreComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Characters/CTurretComponent.h"
#include "Characters/Turrets/CTurret.h"

void UCStoreComponent::ItemPressed(FStoreData InData)
{
	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(GetOwner());
	CheckNull(inventory);

	bool result = inventory->SubMoney(InData.Price);

	if (!result)
	{
		CLog::Print("NotEnoughMoney");
		return;
	}

	USkeletalMeshComponent* skeletal = CHelpers::GetComponent<USkeletalMeshComponent>(GetOwner());
	CheckNull(skeletal);

	FTransform transform = skeletal->GetSocketTransform("Turret_Spawn");
	float yaw = Cast<ACharacter>(GetOwner())->GetControlRotation().Yaw;
	FRotator rotator = FRotator(0, yaw + 180, 0);
	transform.SetRotation(FQuat(rotator));

	ACTurret* turret = GetWorld()->SpawnActorDeferred<ACTurret>(ACTurret::StaticClass(), transform, GetOwner());
	if (turret)
	{
		UGameplayStatics::FinishSpawningActor(turret, transform);
		turret->SetTurret(InData.Type);
		inventory->Root(turret);
	}
}

UCStoreComponent::UCStoreComponent()
{
	CHelpers::GetClass<UCUW_Store>(&StoreWidgetClass, "WidgetBlueprint'/Game/Widgets/BP_CUW_Store.BP_CUW_Store_C'");
}

void UCStoreComponent::BeginPlay()
{
	Super::BeginPlay();

	StoreWidget = CreateWidget<UCUW_Store, APlayerController>(Cast<ACharacter>(GetOwner())->GetController<APlayerController>(), StoreWidgetClass);
	StoreWidget->AddToViewport();
	StoreWidget->OffDisplay();

	StoreWidget->OnStoreItem_Pressed.AddDynamic(this, &UCStoreComponent::ItemPressed);
}

void UCStoreComponent::OnDisplay()
{
	StoreWidget->OnDisplay();
}

void UCStoreComponent::OffDisplay()
{
	StoreWidget->OffDisplay();
}