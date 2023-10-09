#include "CAN_EndDead.h"
#include "Global.h"
#include "Characters/CCharacter.h"

FString UCAN_EndDead::GetNotifyName_Implementation() const
{
	return "EndDead";
}

void UCAN_EndDead::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACCharacter* character = Cast<ACCharacter>(MeshComp->GetOwner());
	CheckNull(character);

	character->EndDead();
}