#include "CTimelineFloatComponent.h"
#include "Global.h"

void UCTimelineFloatComponent::Float(float Output)
{
	if (CurveFloat.IsBound())
		CurveFloat.Broadcast(Output);
}

UCTimelineFloatComponent::UCTimelineFloatComponent()
{
}

void UCTimelineFloatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCTimelineFloatComponent::BindCurve()
{
	CheckNull(Curve);

	UCurveFloat* curveFloat = Cast<UCurveFloat>(Curve);
	CheckNull(curveFloat);

	TimelineFloat.BindUFunction(this, "Float");
	Timeline.AddInterpFloat(curveFloat, TimelineFloat);
}