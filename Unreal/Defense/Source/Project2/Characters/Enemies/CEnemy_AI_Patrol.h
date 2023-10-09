#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/CEnemy_AI.h"
#include "CEnemy_AI_Patrol.generated.h"

UCLASS()
class PROJECT2_API ACEnemy_AI_Patrol : public ACEnemy_AI
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCPatrolComponent* Patrol;

public:
	ACEnemy_AI_Patrol();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void InitBeginPlay() override;
};