#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Slot.generated.h"

UCLASS()
class PROJECT2_API UCUW_Slot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void OnSelected();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void OffSelected();
};