#include "RenderTexture.h"

RenderTexture::RenderTexture()
{
	m_Texture2D = nullptr;
	m_ShaderResourceView = nullptr;
	m_RenderTargetView = nullptr;
}
RenderTexture::RenderTexture(const RenderTexture& other){}
RenderTexture::~RenderTexture(){}

HRESULT RenderTexture::Initialize(ID3D11Device* _device, int _windowWidth, int _windowHeight)
{
	HRESULT result = S_OK;

	D3D11_TEXTURE2D_DESC descTex;
	ZeroMemory(&descTex, sizeof(descTex));
	descTex.ArraySize = 1;
	descTex.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	descTex.Usage = D3D11_USAGE_DEFAULT;
	descTex.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	descTex.Width = _windowWidth;
	descTex.Height = _windowHeight;
	descTex.MipLevels = D3D11_BIND_VERTEX_BUFFER;
	descTex.SampleDesc.Count = 1;
	descTex.CPUAccessFlags = 0;

	result = _device->CreateTexture2D(&descTex, NULL, &m_Texture2D);
	// Create resource view
	result = _device->CreateShaderResourceView(m_Texture2D, NULL, &m_ShaderResourceView);
	// Create render target view
	result = _device->CreateRenderTargetView(m_Texture2D, NULL, &m_RenderTargetView);	

	return result;
}

void RenderTexture::Shutdown()
{
	m_Texture2D->Release();
	m_Texture2D = nullptr;
	m_ShaderResourceView->Release();
	m_ShaderResourceView = nullptr;
	m_RenderTargetView->Release();
	m_RenderTargetView = nullptr;
}

void RenderTexture::SetRenderTarget(ID3D11DeviceContext* _deviceContext)
{
	_deviceContext->OMSetRenderTargets(1, &m_RenderTargetView, NULL);
}
