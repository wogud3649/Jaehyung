#pragma once
class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void CreateBlob(wstring file);
	void CreateInputLayOut();
	void CreateVertexShader();

	void Set();

private:
	Microsoft::WRL::ComPtr<ID3DBlob>					vertexBlob; // VertexShader 만들 때 필요한 애
	Microsoft::WRL::ComPtr<ID3D11VertexShader>          vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>           inputLayOut;
};

