#ifndef VolumeRenderer_h__
#define VolumeRenderer_h__

#include "ModelShader.h"
#include "VolumeRaycastShader.h"
#include "RenderTexture.h"
#include "VolumeTexture.h"
#include "Cube.h"
#include "D3D.h"
#include "VolumeRenderer.h"

__declspec(align(16)) class VolumeRenderer
{
protected:
	struct MatrixBuffer
	{
		XMMATRIX mWVP;
	};
public:
	VolumeRenderer();
	VolumeRenderer(const VolumeRenderer&);
	~VolumeRenderer();

	void* operator new(size_t);
	void operator delete(void*);

	HRESULT Initialize(ID3D11Device*, HWND, int, int);
	void Shutdown();
	void Update(float);
	void Render(ID3D11Device*, ID3D11DeviceContext*, D3D*);

private:
	void CreateSampler(ID3D11Device*);

protected:
	//objects
	ModelShader* m_ModelShader;
	VolumeRaycastShader* m_VolumeRaycastShader;
	RenderTexture* m_ModelFront;
	RenderTexture* m_ModelBack;
	VolumeTexture* m_VolumeTexture;
	Cube* m_cube;
	
	//sampler 
	ID3D11SamplerState* g_pSamplerLinear;

	XMMATRIX viewProj;

};
#endif // VolumeRenderer_h__