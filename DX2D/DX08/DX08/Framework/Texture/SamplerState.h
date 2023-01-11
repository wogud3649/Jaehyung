#pragma once
class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void Set(int slot = 0);
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState>          samplerState; // Sampler -> 판박이를 붙이는 아저씨
};

