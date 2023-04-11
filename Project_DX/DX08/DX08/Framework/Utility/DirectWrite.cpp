#include "framework.h"
#include "DirectWrite.h"

DirectWrite* DirectWrite::_instance = nullptr;

DirectWrite::DirectWrite()
{
	ASSERT(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)_writeFactory.GetAddressOf()));

	ASSERT(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, _factory.GetAddressOf()));

	ComPtr<IDXGIDevice> dxgiDevice;

	ASSERT(DEVICE->QueryInterface(dxgiDevice.GetAddressOf()));

	_factory->CreateDevice(dxgiDevice.Get(), _device.GetAddressOf());

	ASSERT(_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		_dc.GetAddressOf()));

	ComPtr<IDXGISurface> dxgiSurface;
	ASSERT(Device::GetInstance()->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)dxgiSurface.GetAddressOf()));

	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX = 96;
	bp.dpiY = 96;
	bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext = nullptr;

	ASSERT(_dc->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bp, _targetBitmap.GetAddressOf()));

	_dc->SetTarget(_targetBitmap.Get());
}

DirectWrite::~DirectWrite()
{
}

void DirectWrite::RenderText(wstring text, RECT rect, float size, wstring fontPath, XMFLOAT4 color, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch)
{
	FontBrushDesc brushDesc;
	brushDesc._color = color;

	FontBrushDesc* findBrush = nullptr;

	for (auto& desc : _fontBrushes)
	{
		if (desc == brushDesc)
		{
			findBrush = &desc;
			break;
		}
	}

	if (findBrush == nullptr)
	{
		D2D1::ColorF colorF = D2D1::ColorF(color.x, color.y, color.z);
		ASSERT(_dc->CreateSolidColorBrush(colorF, OUT brushDesc._brush.GetAddressOf()));

		_fontBrushes.push_back(brushDesc);
		findBrush = &brushDesc;
	}

	FontTextDesc fontDesc;
	fontDesc._fontPath = fontPath;
	fontDesc._fontSize = size;
	fontDesc._weight = weight;
	fontDesc._style = style;
	fontDesc._stretch = stretch;

	FontTextDesc* findText = nullptr;

	for (auto& desc : _fontTexts)
	{
		if (desc == fontDesc)
		{
			findText = &desc;
			break;
		}
	}

	if (findText == nullptr)
	{
		ASSERT(_writeFactory->CreateTextFormat(fontDesc._fontPath.c_str(), nullptr, fontDesc._weight
			, fontDesc._style, fontDesc._stretch,
			fontDesc._fontSize, L"ko", fontDesc._format.GetAddressOf()));

		_fontTexts.push_back(fontDesc);
		findText = &fontDesc;
	}

	D2D1_RECT_F rectF;
	rectF.left = (float)rect.left;
	rectF.right = (float)rect.right;
	rectF.top = (float)rect.top;
	rectF.bottom = (float)rect.bottom;

	_dc->DrawTextW(text.c_str(), text.size(), findText->_format.Get(), &rectF, findBrush->_brush.Get());
}
