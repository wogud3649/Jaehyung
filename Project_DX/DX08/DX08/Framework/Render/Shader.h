#pragma once
class Shader
{
public:
	Shader() {}
	virtual ~Shader() {}

	virtual void Set() abstract;

protected:
	wstring _file;
	Microsoft::WRL::ComPtr<ID3DBlob> _blob;
};

