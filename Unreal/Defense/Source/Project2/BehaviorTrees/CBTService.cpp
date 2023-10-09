#include "CBTService.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Characters/Enemies/CAIController.h"
#include "Components/Characters/CStatusComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Characters/Enemies/CBehaviorComponent.h"
#include "Components/Objects/CBreakableComponent.h"
#include "Components/Objects/CGunComponent.h"
#include "Objects/CBreakable.h"

UCBTService::UCBTService()
{
    NodeName = "CBTService";
}

void UCBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

    ACCharacter* ai = Cast<ACCharacter>(controller->GetPawn());
    UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(ai);
    UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(ai);

    if (status->IsDead())
    {
        controller->StopMovement();

        return;
    }

    if (status->IsHitted())
    {
        behavior->SetHitted();
        controller->StopMovement();

        return;
    }

    if (inventory)
    {
        AActor* item = inventory->GetSelectedItem();
        if (item)
        {
            UCGunComponent* gun = CHelpers::GetComponent<UCGunComponent>(item);
            if (gun)
            {
                if (gun->GetActiveBullets() == 0)
                {
                    gun->Reload();
                }
            }
        }
    }

    AActor* target = behavior->GetTarget();
    if (!target)
    {
        behavior->SetPatrol();
        return;
    }
    else
    {
        ACBreakable* breakable = Cast<ACBreakable>(target);
        if (breakable)
        {
            UCBreakableComponent* breakableComponent = CHelpers::GetComponent<UCBreakableComponent>(target);
            if (breakableComponent->IsDestroyed())
            {
                behavior->SetWait();
                controller->StopMovement();

                return;
            }
        }

        ACCharacter* character = Cast<ACCharacter>(target);
        if (character)
        {
            UCStatusComponent* targetStatus = CHelpers::GetComponent<UCStatusComponent>(target);
            if (targetStatus->IsDead())
            {
                behavior->SetWait();
                controller->StopMovement();

                return;
            }
        }
    }

    float distance = ai->GetDistanceTo(target);

    if (distance < controller->GetActionRange())
    {
        behavior->SetAction();
        controller->StopMovement();

        return;
    }

    if (distance < controller->GetSightRadius())
    {
        behavior->SetApproach();

        return;
    }
}