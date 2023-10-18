#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

UCLASS()
class DEFENSERPG_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Cursor")
		class UDecalComponent* Decal;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		class UCInventoryComponent* Inventory;

public:
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UDecalComponent* GetDecal() const { return Decal; }

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void TickDecal();

	void OnLeftPressed();
	void OnLeftReleased();
	void On1Pressed();
	void On2Pressed();
	void On3Pressed();
	void On4Pressed();
	void On5Pressed();
	void On6Pressed();
	void On7Pressed();
	void On8Pressed();
	void On9Pressed();
	void On0Pressed();
};