#include "CItemComponent.h"
#include "Global.h"
#include "Engine/DataTable.h"

UCItemComponent::UCItemComponent()
{
}

void UCItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCItemComponent::SetItemCode(int32 ItemCode)
{
	CheckTrue(ItemCode == -1);

	UDataTable* DataTable;
	CHelpers::GetAsset(&DataTable, "DataTable'/Game/Resources/DataTables/ItemDatas.ItemDatas'");

	CheckNull(DataTable);

	TArray<FItemData*> itemDatas;
	DataTable->GetAllRows<FItemData>("", itemDatas);

	for (FItemData* itemData : itemDatas)
	{
		if (itemData->ItemCode == ItemCode)
		{
			Data = *itemData;
			break;
		}
	}
}