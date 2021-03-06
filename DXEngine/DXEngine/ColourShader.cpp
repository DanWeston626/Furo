/// <summary>
/// ColourShader.cpp
///
/// About:
/// ColourShader.h interfaces the Colour.hlsl shader and derives 
/// from the shader base class. The implementation iss based from 
/// the ColorShaderClass found in RasterTek tutorials
///
/// Based from:
/// ColourShaderClass.h - http://www.rastertek.com/dx11tut04.html
/// </summary>

#include "ColourShader.h"

ColourShader::ColourShader()
{
	m_MatrixBuffer = nullptr;
}
ColourShader::ColourShader(const ColourShader& other){}
ColourShader::~ColourShader(){};

HRESULT ColourShader::Initialize(ID3D11Device* _device, HWND _hwn)	
{
	HRESULT result;
	ID3DBlob* blob = nullptr;

#pragma region Vertex Shader
	result = CompileShaderFromFile(L"../Shaders/color.hlsl", "ColorVertexShader", "vs_5_0", &blob);
	result = _device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_VertexShader);
#pragma endregion	

#pragma region Input Layout
	// Shader Input Layout
	D3D11_INPUT_ELEMENT_DESC m_layout[2];
	m_layout[0].SemanticName = "POSITION"; //match name in VS shader
	m_layout[0].SemanticIndex = 0;
	m_layout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	m_layout[0].InputSlot = 0;
	m_layout[0].AlignedByteOffset = 0;
	m_layout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	m_layout[0].InstanceDataStepRate = 0;

	m_layout[1].SemanticName = "COLOR";
	m_layout[1].SemanticIndex = 0;
	m_layout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	m_layout[1].InputSlot = 0;
	m_layout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	m_layout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	m_layout[1].InstanceDataStepRate = 0;
	
	UINT numElements = ARRAYSIZE(m_layout);

	result = _device->CreateInputLayout(m_layout, numElements, blob->GetBufferPointer(), blob->GetBufferSize(), &m_InputLayout);
	blob->Release();
#pragma endregion	

#pragma region Pixel Shader
	blob = nullptr;
	// Compile and create the pixel shader
	result = CompileShaderFromFile(L"../Shaders/color.hlsl", "ColorPixelShader", "ps_5_0", &blob);
	result = _device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &m_PixelShader);
	blob->Release();
#pragma  endregion	

#pragma region Constant Buffers
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(MatrixBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	result = _device->CreateBuffer(&bd, NULL, &m_MatrixBuffer);
#pragma endregion

	return result;
}

void ColourShader::Render(ID3D11DeviceContext* _deviceContext, XMMATRIX* _mWVM, int _indexCount)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBuffer* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	*_mWVM = XMMatrixTranspose(*_mWVM);

	// Lock the constant buffer so it can be written to.
	result = _deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBuffer*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->mWVP = XMMatrixMultiply(Camera::Instance()->GetViewProj(),*_mWVM);

	// Unlock the constant buffer.
	_deviceContext->Unmap(m_MatrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finally set the constant buffer in the vertex shader with the updated values.
	_deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);

	// Set the vertex input layout.
	_deviceContext->IASetInputLayout(m_InputLayout);

	// Set the vertex and pixel shaders that will be used to render this triangle.
	_deviceContext->VSSetShader(m_VertexShader, NULL, 0);
	_deviceContext->PSSetShader(m_PixelShader, NULL, 0);

	// Render the triangle.
	_deviceContext->DrawIndexed(_indexCount, 0, 0);
}

void ColourShader::Shutdown()
{
	ShaderBase::Shutdown();
}