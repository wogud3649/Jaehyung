#include "CTimelineVectorComponent.h"
#include "Global.h"
#include "Curves/CurveVector.h"

void UCTimelineVectorComponent::Vector(FVector Output)
{
	if (CurveVector.IsBound())
		CurveVector.Broadcast(Output);
}

UCTimelineVectorComponent::UCTimelineVectorComponent()
{
}

void UCTimelineVectorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCTimelineVectorComponent::BindCurve()
{
	CheckNull(Curve);

	UCurveVector* curveVector = Cast<UCurveVector>(Curve);
	CheckNull(curveVector);

	TimelineVector.BindUFunction(this, "Vector");
	Timeline.AddInterpVector(curveVector, TimelineVector);
}