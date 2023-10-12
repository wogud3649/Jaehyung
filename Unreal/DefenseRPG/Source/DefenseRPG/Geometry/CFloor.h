#pragma once

#include "CoreMinimal.h"
#include "Geometry/CGeometry.h"
#include "CFloor.generated.h"

UCLASS()
class DEFENSERPG_API ACFloor : public ACGeometry
{
	GENERATED_BODY()

public:
	ACFloor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};