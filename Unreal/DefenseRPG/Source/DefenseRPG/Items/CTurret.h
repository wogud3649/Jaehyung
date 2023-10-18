#pragma once

#include "CoreMinimal.h"
#include "Items/CItem.h"
#include "CTurret.generated.h"

UCLASS()
class DEFENSERPG_API ACTurret : public ACItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* Box;

public:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	ACTurret();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Rooted() override;
	virtual void OnSelected() override;
	virtual void OffSelected() override;
	virtual void Dumped() override;
	virtual bool PlayAction(bool bLeftClick) override;

protected:
	virtual void SetCollisionEnabled(bool bCollisionEnable) override;

private:
	bool bFollowCursor = false;
	bool bPlantable = true;
	bool bPlanted = false;

	class UMaterialInterface* Material;
	UMaterialInterface* IndicatorMaterial;
	class UMaterialInstanceDynamic* DynamicMaterial;
	UMaterialInstanceDynamic* IndicatorDynamicMaterial;
	FLinearColor TurretBaseColor = FLinearColor(0.180000, 0.180000, 0.180000);
	FLinearColor IndicatorBaseColor = FLinearColor(0, 0, 1);
	FLinearColor IndicatorOverlapedColor = FLinearColor(1, 0, 0);
};