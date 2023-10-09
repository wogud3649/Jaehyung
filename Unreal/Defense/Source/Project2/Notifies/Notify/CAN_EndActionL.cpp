#include "CAN_EndActionL.h"
#include "Global.h"
#include "Characters/CCharacter.h"

FString UCAN_EndActionL::GetNotifyName_Implementation() const
{
	return "EndActionL";
}

void UCAN_EndActionL::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACCharacter* character = Cast<ACCharacter>(MeshComp->GetOwner());
	CheckNull(character);
 
	character->EndActionL();
}