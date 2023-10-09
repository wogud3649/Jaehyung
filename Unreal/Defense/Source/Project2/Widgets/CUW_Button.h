#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Button.generated.h"

UCLASS()
class PROJECT2_API UCUW_Button : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Press();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Hover();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Normal();

private:
	UFUNCTION(BlueprintCallable)
		void OnPressed();

private:
	class UCUW_Store* GetStore();
};