#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUW_Inventory.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
};