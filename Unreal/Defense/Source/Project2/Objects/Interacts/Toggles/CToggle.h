#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/CInteract.h"
#include "CToggle.generated.h"

UCLASS()
class PROJECT2_API ACToggle : public ACInteract
{
	GENERATED_BODY()

public:
	ACToggle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override {};
	virtual void EndInteract(AActor* InActor) override {};
};