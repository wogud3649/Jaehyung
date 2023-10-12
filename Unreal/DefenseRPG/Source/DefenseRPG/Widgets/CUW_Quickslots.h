#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Items/CItemComponent.h"
#include "CUW_Quickslots.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Quickslots : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE const TArray<class UCUW_Button*> GetButtons() { return Buttons; }

public:
	virtual void NativeConstruct() override;

	void SetItemData(int32 Index, const FItemData InItemData);

private:
	void SetButtons();

private:
	TArray<UCUW_Button*> Buttons;
};