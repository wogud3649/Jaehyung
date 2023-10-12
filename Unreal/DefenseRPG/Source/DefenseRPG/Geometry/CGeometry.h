#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CGeometry.generated.h"

UCLASS()
class DEFENSERPG_API ACGeometry : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

public:
	ACGeometry();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	void SetMesh(FString InPath);
};