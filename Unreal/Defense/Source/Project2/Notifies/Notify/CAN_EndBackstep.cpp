#include "CAN_EndBackstep.h"
#include "Global.h"
#include "Characters/CCharacter.h"

FString UCAN_EndBackstep::GetNotifyName_Implementation() const
{
	return "EndBackstep";
}

void UCAN_EndBackstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACCharacter* character = Cast<ACCharacter>(MeshComp->GetOwner());
	CheckNull(character);

	character->EndBackstep();
}