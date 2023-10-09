#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Toggles/CToggle.h"
#include "CToggle_BasicShape.generated.h"

UCLASS()
class PROJECT2_API ACToggle_BasicShape : public ACToggle
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBasicShapeComponent* BasicShape;

public:
	ACToggle_BasicShape();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override;
	virtual void EndInteract(AActor* InActor) override;
};