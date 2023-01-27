#pragma once
class PixelShader :public Shader
{
public:
	PixelShader(wstring file);
	virtual ~PixelShader();

	void CreateBlob(wstring file);
	void CreatePixelShader();

	virtual void Set() override;

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
};

