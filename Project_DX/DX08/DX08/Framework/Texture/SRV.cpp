#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring file)
{
    // Textrue�� �غ��ϰ�, shader �ѱ�� �۾�
    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    _size = Vector2(float(image.GetImages()->width), float(image.GetImages()->height));
    // �ǹ��� ������ ����ϴ� �۾�
    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), IN shaderResourceView.GetAddressOf());
}

SRV::~SRV()
{
}

void SRV::Set(int slot)
{
    DC->PSSetShaderResources(slot, 1, shaderResourceView.GetAddressOf());
}

Vector2 SRV::GetImageSize()
{
    return _size;
}
