// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "MyCharacter.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am(TEXT("AnimMontage'/Game/BluePrints/BP_MyCharacterAM.BP_MyCharacterAM'"));

	if (am.Succeeded())
	{
		_attackMontage = am.Object;
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* character = Cast<AMyCharacter>(TryGetPawnOwner());
	if (IsValid(character))
	{
		_speed = character->GetVelocity().Size();
		_isFalling = character->GetMovementComponent()->IsFalling();

		_horizontal = character->GetHorizontal();
		_vertical = character->GetVertical();
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_attackMontage))
	{
		Montage_Play(_attackMontage);
	}
}

void UMyAnimInstance::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName, _attackMontage);
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	_onAttackHit.Broadcast();
}
