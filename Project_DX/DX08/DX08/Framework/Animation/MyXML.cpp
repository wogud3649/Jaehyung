#include "framework.h"
#include "MyXML.h"

MyXML::MyXML(string path, wstring srvPath)
: _path(path)
, _srvPath(srvPath)
{
	_document = make_shared<tinyxml2::XMLDocument>();
	_document->LoadFile(path.c_str());
}

MyXML::~MyXML()
{
}

vector<Action::Clip> MyXML::GetClips(MyXML::Sort sortx, MyXML::Sort sorty)
{
	shared_ptr<SRV> srv = SRV_ADD(_srvPath);

	vector<Action::Clip> result;
	tinyxml2::XMLElement* textureAtlas = _document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	_maxSize = Vector2(0, 0);

	while (true)
	{
		if (row == nullptr)
			break;
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		if (_maxSize.x < w)
			_maxSize.x = w;
		if (_maxSize.y < h)
			_maxSize.y = h;

		row = row->NextSiblingElement();
	}

	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	_averageSize = Vector2(0, 0);

	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();
		int x;
		switch (sortx)
		{
		case MyXML::LEFT:
			x = row->FindAttribute("x")->IntValue();
			break;
		case MyXML::MIDDLE:
			x = row->FindAttribute("x")->IntValue() + (w - _maxSize.x) / 2;
			break;
		case MyXML::RIGHT:
			x = row->FindAttribute("x")->IntValue() + (w - _maxSize.x);
			break;
		default:
			break;
		}

		int y;
		switch (sorty)
		{
		case MyXML::TOP:
			y = row->FindAttribute("y")->IntValue();
			break;
		case MyXML::MIDDLE:
			y = row->FindAttribute("y")->IntValue() + (h - _maxSize.y) / 2;
			break;
		case MyXML::BOTTOM:
			y = row->FindAttribute("y")->IntValue() + (h - _maxSize.y);
			break;
		default:
			break;
		}

		result.emplace_back(x, y, _maxSize.x, _maxSize.y, srv);

		_averageSize.x += w;
		_averageSize.y += h;
		count++;

		row = row->NextSiblingElement();
	}

	_averageSize.x /= count;
	_averageSize.y /= count;

	return result;
}