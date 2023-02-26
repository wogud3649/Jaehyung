#pragma once
class VertexShader : public Shader
{
public:
	VertexShader(wstring file);
	virtual ~VertexShader();

	void CreateBlob(wstring file);
	void CreateInputLayOut();
	void CreateVertexShader();

	virtual void Set() override;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	_inputLayOut;

	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> _reflection;
};

