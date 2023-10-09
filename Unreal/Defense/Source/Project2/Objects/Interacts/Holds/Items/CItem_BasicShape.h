#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/Holds/Items/CItem.h"
#include "CItem_BasicShape.generated.h"

UCLASS()
class PROJECT2_API ACItem_BasicShape : public ACItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBasicShapeComponent* BasicShape;

public:
	ACItem_BasicShape();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override;
	virtual void EndInteract(AActor* InActor) override;

	virtual void BeginRoot(AActor* InActor) override;
	virtual void EndRoot(AActor* InActor) override;
};