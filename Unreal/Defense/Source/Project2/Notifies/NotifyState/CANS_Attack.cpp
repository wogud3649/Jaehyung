#include "CANS_Attack.h"
#include "Global.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Objects/CWeaponComponent.h"

FString UCANS_Attack::GetNotifyName_Implementation() const
{
	return "Attack";
}

void UCANS_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(MeshComp->GetOwner());
	CheckNull(inventory);
	CheckNull(inventory->GetSelectedItem());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(inventory->GetSelectedItem());
	CheckNull(weapon);

	weapon->ActivateCollision();
}

void UCANS_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(MeshComp->GetOwner());
	CheckNull(inventory);
	CheckNull(inventory->GetSelectedItem());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(inventory->GetSelectedItem());
	CheckNull(weapon);

	weapon->DeactivateCollision();
}