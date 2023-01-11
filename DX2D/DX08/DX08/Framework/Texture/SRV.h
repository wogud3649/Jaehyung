#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void Set(int slot = 0);

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    shaderResourceView; // SRV -> 판박이 만드는 아저씨
};

