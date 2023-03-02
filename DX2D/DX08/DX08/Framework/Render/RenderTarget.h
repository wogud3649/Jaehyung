#pragma once
class RenderTarget
{
public:
	RenderTarget(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);
	~RenderTarget();

	void Set(XMFLOAT4 clearColor = XMFLOAT4(1, 1, 1, 1));

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return _srv; }

private:
	void CreateRTVTexture();
	void CreateRTV();
	void CreateSRV();


	UINT _width;
	UINT _height;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> _rtvTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _rtv;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;
};

