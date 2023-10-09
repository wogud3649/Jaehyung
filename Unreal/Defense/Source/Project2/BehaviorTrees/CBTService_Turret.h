#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Turret.generated.h"

UCLASS()
class PROJECT2_API UCBTService_Turret : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_Turret();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};