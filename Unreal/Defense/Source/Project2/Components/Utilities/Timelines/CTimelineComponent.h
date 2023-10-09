#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CTimelineComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCTimelineComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		UCurveBase* Curve;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;

public:
	UCTimelineComponent();

protected:
	virtual void BeginPlay() override;

public:
	void TickTimeline(float DeltaTime);

	void SetCurve(FString InPath);

	void Play();
	void Stop();
	void Reverse();

	virtual void BindCurve() {};

protected:
	FTimeline Timeline;
};