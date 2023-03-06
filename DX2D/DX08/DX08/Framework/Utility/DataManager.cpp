#include "framework.h"
#include "DataManager.h"

DataManager* DataManager::_instance = nullptr;
DataManager::DataManager()
{
	_itemInfo.reserve(5);

	LoadItemInfo();
}

DataManager::~DataManager()
{
}

void DataManager::LoadItemInfo()
{
	_document = make_shared<tinyxml2::XMLDocument>();
	_document->LoadFile("Resource/XML/items.xml");

	tinyxml2::XMLElement* Workbook = _document->FirstChildElement();
	tinyxml2::XMLElement* Worksheet = Workbook->FirstChildElement("Worksheet");
	tinyxml2::XMLElement* table = Worksheet->FirstChildElement();
	tinyxml2::XMLElement* row = table->FirstChildElement();
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
			temp.emplace_back(data->IntText());

			cell = cell->NextSiblingElement();
		}

		info.price = temp[0];
		info.atk = temp[1];
		info.def = temp[2];
		info.rare = temp[3];

		_itemInfo.emplace_back(info);
		row = row->NextSiblingElement();
	}
}
