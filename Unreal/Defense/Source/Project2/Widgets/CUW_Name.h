#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Name.generated.h"

UCLASS()
class PROJECT2_API UCUW_Name : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetNameText(const FString& InName);
};