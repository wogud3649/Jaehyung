#pragma once
using namespace tinyxml2;

class MyXML
{
public:
	MyXML(string path, wstring srvPath);
	~MyXML();
	
	vector<Action::Clip> GetClips();
	Vector2 AverageSize() { return _averageSize; }
private:
	string _path;
	wstring _srvPath;

	shared_ptr<tinyxml2::XMLDocument> _document;

	Vector2 _averageSize;
};

