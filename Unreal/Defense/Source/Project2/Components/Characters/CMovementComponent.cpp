#include "CMovementComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCMovementComponent::UCMovementComponent()
{
}

void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());
	CheckNull(character);

	character->JumpMaxCount = JumpMaxCount;
	character->GetCharacterMovement()->JumpZVelocity = JumpZVelocity;

	UpdateSpeed();
}

void UCMovementComponent::ChangeType(EMovementType InType)
{
	Type = InType;

	UpdateSpeed();
}

void UCMovementComponent::UpdateSpeed()
{
	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(GetOwner());
	CheckNull(movement);

	movement->MaxWalkSpeed = *Speed[(int32)Type];
}
