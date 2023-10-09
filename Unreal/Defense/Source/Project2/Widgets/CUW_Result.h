#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Result.generated.h"

UCLASS()
class PROJECT2_API UCUW_Result : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void Retry();

	UFUNCTION()
		void Exit();

protected:
	virtual void NativeConstruct() override;

public:
	void Win();
	void Lose();

	void OnDisplay();
	void OffDisplay();

private:
	class UTextBlock* ResultText;

	class UButton* RetryButton;
	class UTextBlock* RetryText;

	class UButton* ExitButton;
	class UTextBlock* ExitText;

	bool bResult;
};