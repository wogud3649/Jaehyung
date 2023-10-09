#include "CUW_Inventory.h"
#include "Global.h"

void UCUW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryTextures.SetNum((int32)EItemType::Max);

	CHelpers::GetAssetDynamic(&DataTable, "DataTable'/Game/Widgets/DataTables/DT_Inventory.DT_Inventory'");

	if (!DataTable)
	{
		CLog::Print("NoDataTable");
		return;
	}

	TArray<FInventoryData*> datas;
	DataTable->GetAllRows<FInventoryData>("", datas);

	if (datas.Num() == 0)
	{
		CLog::Print("NoTextureDatas : Inventory");
	}

	for (int32 i = 0; i < datas.Num(); i++)
	{
		InventoryTextures[(int32)datas[i]->Type] = datas[i]->Texture;
	}
}