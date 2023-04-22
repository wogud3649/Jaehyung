// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class UE_PARAGON_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Attack();
	UFUNCTION()
	void AttackCheck();
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* montage, bool bInterrupted);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void UpDown(float value);
	void LeftRight(float value);
	void Yaw(float value);

	float GetVertical() { return _upDown; }
	float GetHorizontal() { return _leftRight; }

private:
	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	float _upDown;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	float _leftRight;

	class USpringArmComponent*		_springArm;
	class UCameraComponent*			_camera;
	class UMyStatComponent*			_stat;
	class UWidgetComponent*			_hpBarWidget;

	class UMyAnimInstance* _animInstance;

	int32 _curAttack = 1;
	bool _isAttack = false;
};
