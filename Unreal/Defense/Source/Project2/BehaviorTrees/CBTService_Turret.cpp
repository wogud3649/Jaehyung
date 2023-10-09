#include "CBTService_Turret.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Characters/Turrets/CAIController_Turret.h"
#include "Components/Characters/CStatusComponent.h"
#include "Components/Characters/CInventoryComponent.h"
#include "Components/Characters/Enemies/CBehaviorComponent.h"
#include "Components/Objects/CBreakableComponent.h"
#include "Components/Objects/CGunComponent.h"

UCBTService_Turret::UCBTService_Turret()
{
    NodeName = "Turret";
}

void UCBTService_Turret::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController_Turret* controller = Cast<ACAIController_Turret>(OwnerComp.GetOwner());
    UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

    ACCharacter* ai = Cast<ACCharacter>(controller->GetPawn());
    UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(ai);
    UCInventoryComponent* inventory = CHelpers::GetComponent<UCInventoryComponent>(ai);

    if (status->IsDead())
        return;

    if (status->IsHitted())
    {
        behavior->SetHitted();

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
    CheckNull(target);

    ACCharacter* character = Cast<ACCharacter>(target);
    if (character)
    {
        UCStatusComponent* targetStatus = CHelpers::GetComponent<UCStatusComponent>(target);
        if (targetStatus->IsDead())
        {
            behavior->SetWait();

            return;
        }
    }

    float distance = ai->GetDistanceTo(target);
    if (distance < controller->GetActionRange())
    {
        behavior->SetAction();

        return;
    }
}