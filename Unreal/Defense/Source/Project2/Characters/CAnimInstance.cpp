#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Objects/CItemComponent.h"

void UCAnimInstance::UpdateItemType(AActor* InActor)
{
	if (!InActor)
	{
		ItemType = EItemType::Default;
		return;
	}

	UCItemComponent* item = CHelpers::GetComponent<UCItemComponent>(InActor);
	if (!item)
	{
		ItemType = EItemType::Default;
		return;
	}

	ItemType = item->GetType();
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character);

	Speed = character->GetVelocity().Size2D();
	Direction = CalculateDirection(character->GetVelocity(), character->GetControlRotation());
	bInAir = character->GetCharacterMovement()->IsFalling();
}