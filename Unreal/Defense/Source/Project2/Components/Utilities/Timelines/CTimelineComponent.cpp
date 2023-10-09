#include "CTimelineComponent.h"
#include "Global.h"

UCTimelineComponent::UCTimelineComponent()
{
}

void UCTimelineComponent::BeginPlay()
{
	Super::BeginPlay();

	BindCurve();

	Timeline.SetPlayRate(PlayRate);
}

void UCTimelineComponent::TickTimeline(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCTimelineComponent::SetCurve(FString InPath)
{
	CHelpers::GetAsset<UCurveBase>(&Curve, InPath);
}

void UCTimelineComponent::Play()
{
	Timeline.Play();
}

void UCTimelineComponent::Stop()
{
	Timeline.Stop();
}

void UCTimelineComponent::Reverse()
{
	Timeline.Reverse();
}