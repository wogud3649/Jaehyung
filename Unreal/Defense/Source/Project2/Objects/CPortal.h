#pragma once

#include "CoreMinimal.h"
#include "Objects/CBasicShape.h"
#include "CPortal.generated.h"

UCLASS()
class PROJECT2_API ACPortal : public ACBasicShape
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCPortalComponent* Portal;

public:
	ACPortal();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};