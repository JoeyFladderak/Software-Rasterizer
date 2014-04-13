// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once

#include "surface.h"
#include "template.h"

namespace Tmpl8 {

class Node;
class Surface;
class RenderTarget;
class Game
{
public:

	void SetTarget( Surface* a_Surface ) { m_Surface = a_Surface; }
	void Init();
	void Delete();
	void Tick( float a_DT );
	void KeyDown( unsigned int code ) {}
	void KeyUp( unsigned int code ) {}
	void MouseMove( unsigned int x, unsigned int y );
	void MouseUp( unsigned int button ) {}
	void MouseDown( unsigned int button ) {}

private:

	Surface* m_Surface;

	RenderTarget* m_MainTarget;
	RenderTarget* m_InsetTarget;

	vector3 m_MousePosition;

	Node* m_F16Flightshow[3];
	Node* m_Scene;
	Node* m_ClassicAirplane;
	Node* m_Normandy;
	Node* m_LegoCar;

	vector3 m_PlanePos;
};

}; // namespace Tmpl8