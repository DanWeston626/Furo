/// <summary>
/// ModelShader.h
///
/// About:
/// ModelShader.h interfaces the model_position.hlsl shader and derives 
/// from the shader base class. 
/// </summary>
#include "ShaderBase.h"
#include "Camera.h"
ShaderBase::ShaderBase()
{
	m_PixelShader = nullptr;
	m_VertexShader = nullptr;
	m_ComputeShader = nullptr;
	m_Sampler = nullptr;
}
ShaderBase::ShaderBase(const ShaderBase& other){}
ShaderBase::~ShaderBase(){};

void* ShaderBase::operator new(size_t memorySize)
{
	return _aligned_malloc(memorySize, 16);

}

void ShaderBase::operator delete(void* memoryBlockPtr)
{
	_aligned_free(memoryBlockPtr);
	return;
}

//Shader compilation helper function - Christian B. Mendl, 2012 - editied by Daniel Weston 
HRESULT ShaderBase::CompileShaderFromFile(WCHAR *ShaderFileName, LPCSTR ShaderEntryPoint, LPCSTR ShaderModel, ID3DBlob **ppBlobOut)
{
	HRESULT hr;

	ID3DBlob *pErrorBlob;
	hr = D3DCompileFromFile(ShaderFileName, NULL, NULL, ShaderEntryPoint, ShaderModel, D3D10_SHADER_ENABLE_STRICTNESS, 0,
		ppBlobOut, &pErrorBlob);

#ifdef _DEBUG
	if (pErrorBlob && FAILED(hr))
	{
		char* _error = (char*)pErrorBlob->GetBufferPointer();

		Debug::Instance()->Log(_error);
	}
#endif

	return hr;
}

void ShaderBase::Shutdown()
{
	m_VertexShader->Release();
	delete m_VertexShader;
	m_PixelShader->Release();
	delete m_PixelShader;
	m_InputLayout->Release();
	delete m_InputLayout;
	m_Sampler->Release();
	delete m_Sampler;
	m_ComputeShader->Release();
	delete m_ComputeShader;
}