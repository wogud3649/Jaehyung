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

vector<Action::Clip> MyXML::GetClips()
{
	shared_ptr<SRV> srv = SRV_ADD(_srvPath);

	vector<Action::Clip> result;
	tinyxml2::XMLElement* textureAtlas = _document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	_averageSize.x = 0;
	_averageSize.y = 0;

	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		result.emplace_back(x, y, w, h, srv);

		_averageSize.x += w;
		_averageSize.y += h;
		count++;

		row = row->NextSiblingElement();
	}

	_averageSize.x /= count;
	_averageSize.y /= count;

	return result;
}
