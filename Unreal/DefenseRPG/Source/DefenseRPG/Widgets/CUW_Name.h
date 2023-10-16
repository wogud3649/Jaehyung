#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Name.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Name : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetNameText(const FString& InName);

private:
	class UTextBlock* Text;
	FString Name;
};