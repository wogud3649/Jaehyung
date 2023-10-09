#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBasicShapeComponent.generated.h"

UENUM(BlueprintType)
enum class EBasicShapeType : uint8
{
	Cube, Cone, Cylinder, Plane, Sphere, Max,
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCBasicShapeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetType(EBasicShapeType InType) { Type = InType; ChangeShape(); }
	FORCEINLINE void SetCube() { Type = EBasicShapeType::Cube; ChangeShape(); }
	FORCEINLINE void SetCone() { Type = EBasicShapeType::Cone; ChangeShape(); }
	FORCEINLINE void SetCylinder() { Type = EBasicShapeType::Cylinder; ChangeShape(); }
	FORCEINLINE void SetPlane() { Type = EBasicShapeType::Plane; ChangeShape(); }
	FORCEINLINE void SetSphere() { Type = EBasicShapeType::Sphere; ChangeShape(); }

private:
	UPROPERTY(EditAnywhere)
		EBasicShapeType Type;

public:
	UCBasicShapeComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void InitShape(UStaticMeshComponent* InMesh);

	void BeginInteract(AActor* InActor);
	void EndInteract();

private:
	FString GetPath();
	void ChangeShape();

private:
	EBasicShapeType OldType;
};