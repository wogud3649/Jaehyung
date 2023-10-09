#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IItem.generated.h"

UINTERFACE(MinimalAPI)
class UIItem : public UInterface
{
	GENERATED_BODY()
};

class PROJECT2_API IIItem
{
	GENERATED_BODY()

public:
	virtual void BeginRoot(AActor* InActor) abstract {}
	virtual void EndRoot(AActor* InActor) abstract {}
	virtual void BeginAction(bool bLeft) abstract {};
	virtual void EndAction(bool bLeft) abstract {};
};