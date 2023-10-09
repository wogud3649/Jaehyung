#include "CANS_EnableNextCombo.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/Characters/CMontageComponent.h"

FString UCANS_EnableNextCombo::GetNotifyName_Implementation() const
{
	return "EnableNext";
}

void UCANS_EnableNextCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACCharacter* character = Cast<ACCharacter>(MeshComp->GetOwner());
	CheckNull(character);

	UCMontageComponent* montage = CHelpers::GetComponent<UCMontageComponent>(character);
	CheckNull(montage);

	CheckFalse(montage->IsEnableNext());

	character->NextMontage();
}

void UCANS_EnableNextCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
}