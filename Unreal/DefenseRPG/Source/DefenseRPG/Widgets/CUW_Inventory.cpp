#include "CUW_Inventory.h"
#include "Global.h"
#include "Widgets/CUW_Quickslots.h"

void UCUW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	CHelpers::GetAssetDynamic(&DataTable, "DataTable'/Game/Resources/DataTables/ItemDatas.ItemDatas'");

	if (!DataTable)
	{
		CLog::Print("NoDataTable");
		return;
	}

	TArray<FItemData*> itemDatas;
	DataTable->GetAllRows<FItemData>("", itemDatas);

	if (itemDatas.Num() == 0)
	{
		CLog::Print("NoTextureDatas : Inventory");
	}

	for (FItemData* itemData : itemDatas)
	{
		ItemDatas.Add(itemData);
	}

	UCUW_Quickslots* quickslots = Cast<UCUW_Quickslots>(GetWidgetFromName("Quickslots"));
	if (quickslots)
	{
		for (int i = 0; i < quickslots->GetNum(); i++)
		{
			quickslots->SetTexture(i, ItemDatas[0]->Texture);
		}
	}
}