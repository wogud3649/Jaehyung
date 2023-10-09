#pragma once

#include "CoreMinimal.h"
#include "Objects/CObject.h"
#include "CBasicShape.generated.h"

UCLASS()
class PROJECT2_API ACBasicShape : public ACObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBasicShapeComponent* BasicShape;

public:
	ACBasicShape();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};