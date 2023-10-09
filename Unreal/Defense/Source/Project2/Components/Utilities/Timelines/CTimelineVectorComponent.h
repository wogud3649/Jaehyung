#pragma once

#include "CoreMinimal.h"
#include "Components/Utilities/Timelines/CTimelineComponent.h"
#include "CTimelineVectorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurveVector, FVector, Output);

UCLASS()
class PROJECT2_API UCTimelineVectorComponent : public UCTimelineComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void Vector(FVector Output);

public:
	UPROPERTY(BlueprintAssignable)
		FCurveVector CurveVector;

public:
	UCTimelineVectorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void BindCurve() override;

private:
	FOnTimelineVector TimelineVector;
};