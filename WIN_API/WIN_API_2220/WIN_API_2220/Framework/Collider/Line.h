#pragma once
class Line
{
public:
	struct Result
	{
		Vector2 contact = { 0,0 };
		bool isCollision = false;
	};

	Line();
	~Line();

	void Update();
	void Render(HDC hdc);

	void SetRed() { _curPen = _pens[0]; }
	void SetGreen() { _curPen = _pens[1]; }

	Vector2 _startPos = { 0,0 };
	Vector2 _endPos = { 0,0 };

	Result IsCollision(shared_ptr<Line> line);

private:
	vector<HPEN> _pens;
	HPEN _curPen;
};

