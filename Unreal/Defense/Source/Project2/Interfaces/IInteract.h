#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteract.generated.h"

UINTERFACE(MinimalAPI)
class UIInteract : public UInterface
{
	GENERATED_BODY()
};

class PROJECT2_API IIInteract
{
	GENERATED_BODY()

public:
	virtual void BeginInteract(AActor* InActor) abstract {}
	virtual void EndInteract(AActor* InActor) abstract {}
};