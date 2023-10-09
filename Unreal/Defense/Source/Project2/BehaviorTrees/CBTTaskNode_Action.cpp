#include "CBTTaskNode_Action.h"
#include "Global.h"
#include "Characters/Enemies/CAIController.h"
#include "Components/Characters/CStatusComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "AIController.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
    bNotifyTick = true;

    NodeName = "Action";
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* controller = Cast<AAIController>(OwnerComp.GetAIOwner());
    ACCharacter* ai = Cast<ACCharacter>(controller->GetPawn());
    UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(ai);
    UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(ai);

    if (status)
        status->SetType(EStatusType::ActionL);

    if (inventory)
        inventory->BeginAction(true);

    TotalTime = 0.0f;

    return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* controller = Cast<AAIController>(OwnerComp.GetAIOwner());
    UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(controller->GetPawn());

    TotalTime += DeltaSeconds;

    if (status->IsIdle() && TotalTime > Delay)
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}