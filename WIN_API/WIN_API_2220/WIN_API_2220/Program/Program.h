#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update(); // Update
	void Render(HDC hdc); // Render

	static HDC _backBuffer;

private:
	unordered_map<string, shared_ptr<Scene>> _sceneTable;
	shared_ptr<Scene> _curScene;

	HBITMAP _hBit;
};