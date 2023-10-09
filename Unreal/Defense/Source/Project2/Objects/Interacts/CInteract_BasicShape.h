#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/CInteract.h"
#include "CInteract_BasicShape.generated.h"

UCLASS()
class PROJECT2_API ACInteract_BasicShape : public ACInteract
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBasicShapeComponent* BasicShape;

public:
	ACInteract_BasicShape();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override {};
	virtual void EndInteract(AActor* InActor) override {};
};