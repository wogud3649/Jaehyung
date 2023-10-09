#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/CHold.h"
#include "CHold_BasicShape.generated.h"

UCLASS()
class PROJECT2_API ACHold_BasicShape : public ACHold
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBasicShapeComponent* BasicShape;

public:
	ACHold_BasicShape();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override;
	virtual void EndInteract(AActor* InActor) override;
};