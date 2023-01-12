#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void Set(int slot = 0);

	Vector2 GetImageSize();

private:
	Vector2 _size;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView; // SRV -> 판박이 만드는 아저씨
};

