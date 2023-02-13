#pragma once
class Planet
{
public:
	Planet(wstring path);
	~Planet();

	void Update();
	void Render();

	void SetParent(shared_ptr<Transform> transform) { _quad->GetTransform()->SetParent(transform); }
	shared_ptr<Transform> GetVirtualTransform() { return _virtualTrans; }
	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	void SetPos(Vector2 pos);
	void SetScale(Vector2 scale);

	float& GetSpeed() { return _speed; }

private:
	shared_ptr<Quad> _quad;
	// 컴포넌트 패턴
	// 부품 붙이기

	shared_ptr<Transform> _virtualTrans;
	shared_ptr<ReverseBuffer> _reverseBuffer;
	shared_ptr<FilterBuffer> _filterBuffer;

	float _speed = 0.0001f;
};

