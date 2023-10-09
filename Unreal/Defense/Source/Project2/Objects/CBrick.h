#pragma once

#include "CoreMinimal.h"
#include "Objects/CBasicShape.h"
#include "CBrick.generated.h"

UCLASS()
class PROJECT2_API ACBrick : public ACBasicShape
{
	GENERATED_BODY()

public:
	ACBrick();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};