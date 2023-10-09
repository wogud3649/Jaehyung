#include "CBTTaskNode_Patrol.h"
#include "Global.h"
#include "Characters/Enemies/CEnemy_AI.h"
#include "Characters/Enemies/CAIController.h"
#include "Components/Characters/CStatusComponent.h"
#include "Components/Characters/Enemies/CPatrolComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
    bNotifyTick = true;

    NodeName = "Patrol";
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* controller = Cast<AAIController>(OwnerComp.GetOwner());
    ACCharacter* ai = Cast<ACCharacter>(controller->GetPawn());
    Patrol = CHelpers::GetComponent<UCPatrolComponent>(ai);

    if (Patrol->IsValidPath())
    {
        EPathFollowingRequestResult::Type result;
        result = controller->MoveToLocation(Patrol->GetIndexLocation(), Patrol->GetAcceptanceDistance());

        switch (result)
        {
        case EPathFollowingRequestResult::Failed:
            return EBTNodeResult::Failed;
            break;
        case EPathFollowingRequestResult::AlreadyAtGoal:
            if (!Patrol->IsLastIndex())
            {
                Patrol->UpdateNextIndex();
            }
            return EBTNodeResult::Succeeded;
            break;
        case EPathFollowingRequestResult::RequestSuccessful:
            break;
        }
    }
    else
    {
        return EBTNodeResult::Failed;
    }

    TotalTime = 0;

    return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    TotalTime += DeltaSeconds; 

    if (TotalTime > Delay)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}