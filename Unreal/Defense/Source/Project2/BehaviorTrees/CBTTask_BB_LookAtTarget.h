#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CBTTask_BB_LookAtTarget.generated.h"

UCLASS()
class PROJECT2_API UCBTTask_BB_LookAtTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCBTTask_BB_LookAtTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	EBTNodeResult::Type PerformLookAtTarget(UBehaviorTreeComponent& OwnerComp);
};