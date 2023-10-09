#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CPlayer.generated.h"

UCLASS()
class PROJECT2_API ACPlayer : public ACCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	UPROPERTY(VisibleDefaultsOnly)
		class UCTraceComponent* Trace;

	UPROPERTY(VisibleDefaultsOnly)
		class UCCrossHairComponent* CrossHair;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStoreComponent* Store;

	UPROPERTY(VisibleDefaultsOnly)
		class UCResultComponent* Result;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void EndDead() override;

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnScroll(float InAxis);

	void BeginSprint();
	void EndSprint();
	void BeginJump();
	void EndJump();
	void BeginInteract();
	void EndInteract();
	void BeginActionL();
	void EndActionL();
	void BeginActionR();
	void EndActionR();
	void Dump();
	void Reload();
	void Build();

	void Num1();
	void Num2();
	void Num3();
	void Num4();
	void Num5();
	void Num6();
	void Num7();
	void Num8();
	void Num9();
	void Num0();
};