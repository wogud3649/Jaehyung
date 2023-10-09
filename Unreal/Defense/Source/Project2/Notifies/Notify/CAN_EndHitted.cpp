#include "CAN_EndHitted.h"
#include "Global.h"
#include "Characters/CCharacter.h"

FString UCAN_EndHitted::GetNotifyName_Implementation() const
{
	return "EndHitted";
}

void UCAN_EndHitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACCharacter* character = Cast<ACCharacter>(MeshComp->GetOwner());
	CheckNull(character);

	character->EndHitted();
}