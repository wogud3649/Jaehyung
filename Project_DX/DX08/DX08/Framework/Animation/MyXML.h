#pragma once
using namespace tinyxml2;

class MyXML
{
public:
	enum Sort
	{
		LEFT,
		TOP,
		MIDDLE,
		RIGHT,
		BOTTOM
	};
	MyXML(string path, wstring srvPath);
	~MyXML();
	
	vector<Action::Clip> GetClips();
	vector<Action::Clip> GetClips(MyXML::Sort sortX = MyXML::Sort::RIGHT, MyXML::Sort sortY = MyXML::Sort::BOTTOM);
	Vector2 AverageSize() { return _averageSize; }
	Vector2 MaxSize() { return _maxSize; }
private:

	string _path;
	wstring _srvPath;

	shared_ptr<tinyxml2::XMLDocument> _document;

	Vector2 _averageSize;
	Vector2 _maxSize;
};

