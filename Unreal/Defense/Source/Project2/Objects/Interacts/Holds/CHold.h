#pragma once

#include "CoreMinimal.h"
#include "Objects/Interacts/CInteract.h"
#include "CHold.generated.h"

UCLASS()
class PROJECT2_API ACHold : public ACInteract
{
	GENERATED_BODY()

public:
	ACHold();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract(AActor* InActor) override {};
	virtual void EndInteract(AActor* InActor) override {};
};