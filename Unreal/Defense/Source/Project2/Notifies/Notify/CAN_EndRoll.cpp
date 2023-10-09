#include "CAN_EndRoll.h"
#include "Global.h"
#include "Characters/CCharacter.h"

FString UCAN_EndRoll::GetNotifyName_Implementation() const
{
	return "EndRoll";
}

void UCAN_EndRoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACCharacter* character = Cast<ACCharacter>(MeshComp->GetOwner());
	CheckNull(character);

	character->EndRoll();
}