#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_CrossHair.generated.h"

UCLASS()
class PROJECT2_API UCUW_CrossHair : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnFocus();

	UFUNCTION(BlueprintImplementableEvent)
		void OffFocus();

	UFUNCTION(BlueprintImplementableEvent)
		void OnDisplay();

	UFUNCTION(BlueprintImplementableEvent)
		void OffDisplay();

public:
	FORCEINLINE bool IsFocus() { return bFocus; }
	FORCEINLINE bool IsDisplay() { return bDisplay; }

public:
	UPROPERTY(BlueprintReadWrite)
		bool bFocus;

	UPROPERTY(BlueprintReadWrite)
		bool bDisplay = true;
};