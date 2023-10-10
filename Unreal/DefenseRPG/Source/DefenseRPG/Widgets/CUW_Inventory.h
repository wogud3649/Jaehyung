#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Components/Items/CItemComponent.h"
#include "CUW_Inventory.generated.h"

UCLASS()
class DEFENSERPG_API UCUW_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UDataTable* DataTable;
	TArray<FItemData*> ItemDatas;
};