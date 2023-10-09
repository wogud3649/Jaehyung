#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController_Turret.generated.h"

UCLASS()
class PROJECT2_API ACAIController_Turret : public AAIController
{
	GENERATED_BODY()

private:
    UFUNCTION()
        void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);

public:
    FORCEINLINE float GetActionRange() { return ActionRange; }
    FORCEINLINE class UAISenseConfig_Sight* GetSight() { return Sight; };

private:
    UPROPERTY(EditAnywhere)
        float ActionRange = 150;

    UPROPERTY(EditAnywhere)
        bool bDrawDebug = false;

    UPROPERTY(EditAnywhere)
        float AdjustCircleHeight = 50;

private:
    UPROPERTY(VisibleDefaultsOnly)
        class UAIPerceptionComponent* Perception;

    UPROPERTY(VisibleDefaultsOnly)
        class UCBehaviorComponent* Behavior;

public:
    ACAIController_Turret();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void SetActionRange(float InActionRange);
    float GetSightRadius();

protected:
    virtual void OnPossess(APawn* InPawn) override;
    virtual void OnUnPossess() override;

private:
    class ACCharacter* Pawn;
    class UAISenseConfig_Sight* Sight;
	
};