#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Health.generated.h"

UCLASS()
class PROJECT2_API UCUW_Health : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void Update(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent)
		void OnDisplay();

	UFUNCTION(BlueprintImplementableEvent)
		void OffDisplay();

	FORCEINLINE bool IsDisplay() { return bDisplay; }

public:
	UPROPERTY(BlueprintReadWrite)
		bool bDisplay = true;
};