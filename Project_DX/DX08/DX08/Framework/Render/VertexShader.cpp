#include "framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
    _file = file;
	CreateBlob(file);
	CreateInputLayOut();
	CreateVertexShader();
}

VertexShader::~VertexShader()
{
}

void VertexShader::CreateBlob(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	D3DCompileFromFile(file.c_str(), nullptr, nullptr,
		"VS", "vs_5_0", flags, 0, _blob.GetAddressOf(), nullptr);
}

void VertexShader::CreateInputLayOut()
{
    // Vertex정보를 넘길 때, 설명서
    D3D11_INPUT_ELEMENT_DESC layOut[] =
    {
        {
            "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,
            D3D11_INPUT_PER_VERTEX_DATA,0
        },
        {
            "UV",0,DXGI_FORMAT_R32G32_FLOAT,0,12,
            D3D11_INPUT_PER_VERTEX_DATA,0
        }
    };

    UINT layoutSize = ARRAYSIZE(layOut);

	DEVICE->CreateInputLayout(layOut, layoutSize, _blob->GetBufferPointer(), _blob->GetBufferSize(), inputLayOut.GetAddressOf());

}

void VertexShader::CreateVertexShader()
{
    DEVICE->CreateVertexShader(_blob->GetBufferPointer(), _blob->GetBufferSize(),
        nullptr, vertexShader.GetAddressOf());
}

void VertexShader::Set()
{
    DC->IASetInputLayout(inputLayOut.Get());
    DC->VSSetShader(vertexShader.Get(), nullptr, 0);
}
