#pragma once
class Cup_Bg
{
public:
	Cup_Bg();
	~Cup_Bg();

	void Update();
	void Render();

	void SetPos(Vector2 pos) { _bg->GetTransform()->GetPos() = pos; }

private:
	shared_ptr<Quad> _bg;
	shared_ptr<Quad> _ground;
};

