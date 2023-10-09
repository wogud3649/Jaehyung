#include "CBTTask_BB_LookAtTarget.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AIController.h"

UCBTTask_BB_LookAtTarget::UCBTTask_BB_LookAtTarget()
{
    bNotifyTick = true;

    NodeName = "LookAtTarget";
    BlackboardKey.SelectedKeyName = "Target";
}

EBTNodeResult::Type UCBTTask_BB_LookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

    NodeResult = PerformLookAtTarget(OwnerComp);

    return NodeResult;
}

EBTNodeResult::Type UCBTTask_BB_LookAtTarget::PerformLookAtTarget(UBehaviorTreeComponent& OwnerComp)
{
    const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

    EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
    if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
    {
        UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
        AActor* target = Cast<AActor>(KeyValue);
        if (target)
        {
            AAIController* controller = Cast<AAIController>(OwnerComp.GetAIOwner());
            APawn* pawn = controller->GetPawn();
            FRotator rotator = FRotator(0);
            rotator.Yaw = UKismetMathLibrary::FindLookAtRotation(pawn->GetActorLocation(), target->GetActorLocation()).Yaw;

            pawn->SetActorRotation(rotator);
            NodeResult = EBTNodeResult::Succeeded;
        }
    }

    return NodeResult;
}
