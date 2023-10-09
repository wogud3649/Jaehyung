#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Widgets/CUW_Result.h"
#include "CResultComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2_API UCResultComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<UCUW_Result> ResultWidgetClass;

public:
	UCResultComponent();

protected:
	virtual void BeginPlay() override;

public:
	void Win();
	void Lose();
	void OnDisplay();
	void OffDisplay();

private:
	UCUW_Result* ResultWidget;
};