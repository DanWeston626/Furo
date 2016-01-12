#include "Furo.h"

Furo::Furo()
{
	//initialize pointers 
	m_textureFluid = 0;
}

Furo::~Furo()
{
}

void Furo::Initialize(FluidField _type, int size, float dt)
{
	m_simulationType = _type;
	switch (_type)
	{
	case TwoDimensional:
		m_textureFluid = new FluidTwoDimensional;
		m_textureFluid->Initialize(size);
		break;
	case ThreeDimensional:
		break;
	default:
		break;
	}
}

void Furo::Run(float dt)
{
	switch (m_simulationType)
	{
	case TwoDimensional:
		m_textureFluid->Update(dt);
		break;
	case ThreeDimensional:
		break;
	default:
		break;
	}
}

void Furo::Shutdown()
{
	m_textureFluid->Shutdown();
}

Fluid* Furo::GetFluid()
{
	switch (m_simulationType)
	{
	case Furo::TwoDimensional:
		return m_textureFluid;
		break;
	case Furo::ThreeDimensional:
		break;
	default:
		return nullptr;
		break;
	}
}