#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CObject.generated.h"

UCLASS()
class PROJECT2_API ACObject : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* Scene;

public:
	ACObject();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	void SetMesh(UStaticMeshComponent* InMesh, FString InPath);
	void SetMesh(USkeletalMeshComponent* InMesh, FString InPath);
	void SetIgnoreActor(UMeshComponent* InMesh, AActor* InActor, bool bIgnore = true);
	void AttachToComponent_World(UMeshComponent* InMesh, USceneComponent* InParent, FName SocketName = NAME_None, bool bSimulatePhysics = false);
	void AttachToComponent_Relative(UMeshComponent* InMesh, USceneComponent* InParent, FName SocketName = NAME_None, bool bSimulatePhysics = false);
	void DetachFromComponent(UMeshComponent* InMesh, USceneComponent* InParent, FDetachmentTransformRules DetachmentRule, bool bSimulatePhysics = false);

private:
	void SetDynamicMaterial(UMeshComponent* InMesh);

protected:
	TArray<class UMaterialInstanceDynamic*> DynamicMaterials;
};