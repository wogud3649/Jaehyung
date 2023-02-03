#pragma once
class BlendState
{
public:
	BlendState();
	~BlendState();

	void SetState();

	void Alpha();
	void Additive();

	void Change();

private:
	Microsoft::WRL::ComPtr<ID3D11BlendState> _curState;
	D3D11_BLEND_DESC _desc = {};
};