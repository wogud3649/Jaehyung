#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/CEnemy.h"
#include "CDummy.generated.h"

UCLASS()
class PROJECT2_API ACDummy : public ACEnemy
{
	GENERATED_BODY()

public:
	ACDummy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};