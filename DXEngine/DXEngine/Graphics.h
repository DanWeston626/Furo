#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <windows.h>
#include "D3D.h"

#include "ModelShader.h"
#include "VolumeRaycastShader.h"
#include "RenderTexture.h"
#include "VolumeTexture.h"
#include "Cube.h"
#include "Quad.h"
#include "VolumeRenderer.h"
#include "Camera.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

__declspec(align(16)) class Graphics
{

protected:
	struct MatrixBuffer
	{
		XMMATRIX mWVP;
	};

public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	void* operator new(size_t);
	void operator delete(void*);

	HRESULT Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float);

private:
	void Update(float);
	bool Render(float);

	//create sampler
	void CreateSampler(ID3D11Device*);
private:
	//engine objects
	D3D* m_D3D;
	ModelShader* m_ModelShader;
	VolumeRaycastShader* m_VolumeRaycastShader;
	RenderTexture* m_ModelFront;
	RenderTexture* m_ModelBack;
	VolumeTexture* m_VolumeTexture;
	VolumeRenderer* m_VolumeRenderer;
	float result;
	Cube* m_cube;
	Quad* m_Quad;

	//sampler 
	ID3D11SamplerState* g_pSamplerLinear;

	XMMATRIX viewProj;	
};

#endif