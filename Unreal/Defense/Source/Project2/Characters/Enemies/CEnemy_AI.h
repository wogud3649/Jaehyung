#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class PROJECT2_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
        class UBehaviorTree* BehaviorTree;

public:
    FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

public:
    ACEnemy_AI();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void InitBeginPlay() override;
};