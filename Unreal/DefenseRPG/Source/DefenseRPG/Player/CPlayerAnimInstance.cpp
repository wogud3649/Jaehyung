#include "CPlayerAnimInstance.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CPlayer.h"

void UCPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACPlayer* player = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(player);

	Speed = player->GetVelocity().Size2D();
	Direction = CalculateDirection(player->GetVelocity(), player->GetControlRotation());
	bInAir = player->GetCharacterMovement()->IsFalling();
}