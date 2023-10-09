#pragma once

#include "CoreMinimal.h"
#include "Components/Utilities/Timelines/CTimelineFloatComponent.h"
#include "CZoomComponent.generated.h"

UCLASS()
class PROJECT2_API UCZoomComponent : public UCTimelineFloatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void Zoom(float Output);

public:
	FORCEINLINE void SetSpringArm(class USpringArmComponent* InSpringArm) { SpringArm = InSpringArm; }

public:
	UCZoomComponent();

protected:
	virtual void BeginPlay() override;

private:
	class USpringArmComponent* SpringArm;
};