
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <windows.h>
#include "D3D.h"

#include "camera.h"
#include "VertexModel.h"
#include "colorshader.h"
#include "Quad.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:

	D3D* m_D3D;
	Camera* m_Camera;
	VertexModel* m_Model;
	ColorShader* m_ColorShader;
	Quad* m_Quad;

};

#endif
