#pragma once

#include "CoreMinimal.h"
#include "Widgets/CUW_Button.h"
#include "CUW_StoreButton.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_StoreButton : public UCUW_Button
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void SetItemData(FItemData InItemData);
};