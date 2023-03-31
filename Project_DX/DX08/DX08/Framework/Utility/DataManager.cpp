#include "framework.h"
#include "DataManager.h"

DataManager* DataManager::_instance = nullptr;
DataManager::DataManager()
{
	_itemTable[0] = ItemInfo();
	LoadItemInfo();
}

DataManager::~DataManager()
{
}

void DataManager::LoadItemInfo()
{
	_document = make_shared<tinyxml2::XMLDocument>();
	_document->LoadFile("Resources/XML/ItemInfo/itemData.xml");

	tinyxml2::XMLElement* workbook = _document->FirstChildElement();
	tinyxml2::XMLElement* worksheet = workbook->FirstChildElement("Worksheet");
	tinyxml2::XMLElement* table = worksheet->FirstChildElement();
	tinyxml2::XMLElement* row = table->FirstChildElement("Row");
	row = row->NextSiblingElement();

	while (true)
	{
		if (row == nullptr)
			break;

		tinyxml2::XMLElement* cell = row->FirstChildElement();
		tinyxml2::XMLElement* data = cell->FirstChildElement();

		ItemInfo info;

		info.name = data->GetText();
		cell = cell->NextSiblingElement();

		vector<int> temp;
		while (true)
		{
			if (cell == nullptr)
				break;

			data = cell->FirstChildElement();
			temp.push_back(data->IntText());
			cell = cell->NextSiblingElement();
		}

		info.itemCode = temp[0];
		info.itemType = static_cast<ItemType>(temp[1]);
		info.rare = temp[2];
		info.price = temp[3];
		info.ad = temp[4];
		info.ap = temp[5];
		info.hp = temp[6];
		info.def = temp[7];
		info.ccd = temp[8];
		info.scd = temp[9];
		info.crp = temp[10];
		info.condition = temp[11];
		info.frameX = temp[12];
		info.frameY = temp[13];

		_itemTable[info.itemCode] = info;
		row = row->NextSiblingElement();
	}
}

const ItemInfo& DataManager::GetItemByItemCode(int itemCode)
{
	if (_itemTable.count(itemCode) == 0)
		return _itemTable[0];
	return _itemTable[itemCode];
}
