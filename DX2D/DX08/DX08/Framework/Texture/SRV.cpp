#include "framework.h"
#include "SRV.h"

SRV::SRV(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv)
: _srv(srv)
{
}

SRV::SRV(wstring file)
{
    // Textrue�� �غ��ϰ�, shader �ѱ�� �۾�
    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    _size = Vector2(float(image.GetImages()->width), float(image.GetImages()->height));
    // �ǹ��� ������ ����ϴ� �۾�
    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), IN _srv.GetAddressOf());
}

SRV::~SRV()
{
}

void SRV::Set(int slot)
{
    DC->PSSetShaderResources(slot, 1, _srv.GetAddressOf());
}

Vector2 SRV::GetImageSize()
{
    return _size;
}
