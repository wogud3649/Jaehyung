#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPatrolComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetPatrolPath(class ACPatrolPath* InPath) { PatrolPath = InPath; }
	FORCEINLINE float GetAcceptanceDistance() { return AcceptanceDistance; }
	FORCEINLINE int32 GetIndex() { return Index; }
	FORCEINLINE bool IsLastIndex() { return GetIndex() == GetSplineCount() - 1; }

private:
	UPROPERTY(EditAnywhere)
		class ACPatrolPath* PatrolPath;

public:
	UCPatrolComponent();

protected:
	virtual void BeginPlay() override;

public:
	bool IsValidPath();
	FVector GetIndexLocation();
	void UpdateNextIndex();
	int32 GetSplineCount();

private:
	int32 Index;
	bool bReverse;
	float AcceptanceDistance = 50.0f;
};