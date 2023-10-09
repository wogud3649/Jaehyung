#pragma once

#include "CoreMinimal.h"
#include "Components/Utilities/Timelines/CTimelineComponent.h"
#include "CTimelineFloatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurveFloat, float, Output);

UCLASS()
class PROJECT2_API UCTimelineFloatComponent : public UCTimelineComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void Float(float Output);

protected:
	UPROPERTY(BlueprintAssignable)
		FCurveFloat CurveFloat;

public:
	UCTimelineFloatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void BindCurve() override;

protected:
	FOnTimelineFloat TimelineFloat;
};