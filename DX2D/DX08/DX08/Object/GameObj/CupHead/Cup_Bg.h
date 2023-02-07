#pragma once
class Cup_Bg
{
public:
	Cup_Bg();
	~Cup_Bg();

	void Update();
	void Render();

	void SetPos(Vector2 pos) { _bg->GetTransform()->GetPos() = pos; }

	shared_ptr<RectCollider> GetCollider() { return _col; }

private:
	shared_ptr<Quad> _bg;
	
	shared_ptr<RectCollider> _col;
	shared_ptr<Quad> _ground;
};

