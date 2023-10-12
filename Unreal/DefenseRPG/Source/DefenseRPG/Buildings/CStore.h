#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStore.generated.h"

UCLASS()
class DEFENSERPG_API ACStore : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Scene")
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = "Store")
		class UCStoreComponent* Store;

public:
	ACStore();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};