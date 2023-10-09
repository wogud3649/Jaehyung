#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "CPatrolPath.generated.h"

UCLASS()
class PROJECT2_API ACPatrolPath : public AActor
{
	GENERATED_BODY()

public:
	FORCEINLINE FVector GetLocationAtSplinePoint(int32 InIndex, ESplineCoordinateSpace::Type CoordinateSpace) { return Spline->GetLocationAtSplinePoint(InIndex, CoordinateSpace); }
	FORCEINLINE bool IsClosedLoop() { return Spline->IsClosedLoop(); }
	FORCEINLINE int32 GetNumberOfSplinePoints() { return Spline->GetNumberOfSplinePoints(); }

private:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;
	
public:
	ACPatrolPath();

protected:
	virtual void BeginPlay() override;
};