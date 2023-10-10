#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Quickslots.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Quickslots : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetNum() { return Buttons.Num(); }

public:
	virtual void NativeConstruct() override;

	void SetTexture(int32 Index, class UTexture2D* Texture);

private:
	TArray<class UCUW_Button*> Buttons;
};