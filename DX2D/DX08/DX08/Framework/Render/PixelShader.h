#pragma once
class PixelShader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	void CreateBlob(wstring file);
	void CreatePixelShader();

	void Set();

private:
	Microsoft::WRL::ComPtr<ID3DBlob> pixelBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

