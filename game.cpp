// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009
#include "Core.h"
#include "Scenegraph.h"
#include "string.h"
#include "game.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include <windows.h>

using namespace Tmpl8;

void Game::Init()
{
	// create the scenemanager and all it contains
	SceneManager::Create();
	// and set the camera.
	SceneManager::Get()->GetScene()->GetCamera()->SetPosition(vector3(0, 0, 0));
	SceneManager::Get()->GetScene()->GetCamera()->SetPan(-40);

	// create the core
 	Core::Create();

	// create the 2 rendertargets, one for the main static screen
	// and one for the following camera.
	m_MainTarget = new RenderTarget(SCRWIDTH, SCRHEIGHT);
	m_InsetTarget = new RenderTarget(256, 186);

	// create the models
	// these 3 are tied together to show that the scenegraph is working correctly
	m_F16Flightshow[0] = SceneManager::Get()->GetScene()->GetRootNode()->AddChild("f16.obj", "plane1");
 	m_F16Flightshow[1] = m_F16Flightshow[0]->AddChild("f16.obj", "plane2");
 	m_F16Flightshow[2] = m_F16Flightshow[0]->AddChild("f16.obj", "plane3");

	m_ClassicAirplane = SceneManager::Get()->GetScene()->GetRootNode()->AddChild("airplane.obj", "sexyplane");
	m_Scene = SceneManager::Get()->GetScene()->GetRootNode()->AddChild("modernroom_early.obj", "indoorscene");
	m_Normandy = SceneManager::Get()->GetScene()->GetRootNode()->AddChild("normandy.obj", "normandy");
	m_LegoCar = SceneManager::Get()->GetScene()->GetRootNode()->AddChild("legocar.obj", "legocar"); 
	
	m_ClassicAirplane->Scale(0.5f);
	m_ClassicAirplane->GetPosition() = vector3( 10, -16, 5 );

	m_Normandy->Scale(5.0f);
	m_Normandy->GetPosition() = vector3( -15, 5, -5 );

	m_LegoCar->GetPosition() = vector3(-20, -13, 0);
	m_LegoCar->Scale(30.0f);
	m_LegoCar->SetPan(-50);

 	for(unsigned int i = 0; i < 3; ++i)
 	{
		m_F16Flightshow[i]->Scale(0.05f);
	}

	m_F16Flightshow[0]->GetPosition() = vector3( -30, -5, -20 );
 	m_F16Flightshow[1]->GetPosition() = vector3( 5, 0, 0 );
 	m_F16Flightshow[2]->GetPosition() = vector3( -5, 0, 0 );

	SceneManager::Get()->GetScene()->GetInsetCamera()->SetPosition(vector3( 0, -15, 30 ));
}

void Game::Tick( float a_DT )
{
	// move the airplane
	static const float rotSpeed		= 0.01f;
	static const float moveSpeed	= 0.0025f;

 	if( GetAsyncKeyState( 'A' ) )		m_F16Flightshow[0]->GetPosition()	-= m_F16Flightshow[0]->GetSide()	* a_DT * moveSpeed;
 	if( GetAsyncKeyState( 'D' ) )		m_F16Flightshow[0]->GetPosition()	+= m_F16Flightshow[0]->GetSide()	* a_DT * moveSpeed;
 	if( GetAsyncKeyState( 'W' ) )		m_F16Flightshow[0]->GetPosition()	+= m_F16Flightshow[0]->GetForward()	* a_DT * moveSpeed;
 	if( GetAsyncKeyState( 'S' ) )		m_F16Flightshow[0]->GetPosition()	-= m_F16Flightshow[0]->GetForward()	* a_DT * moveSpeed;
 	if( GetAsyncKeyState( 'R' ) )		m_F16Flightshow[0]->GetPosition()	+= m_F16Flightshow[0]->GetUp()		* a_DT * moveSpeed;
 	if( GetAsyncKeyState( 'F' ) )		m_F16Flightshow[0]->GetPosition()	-= m_F16Flightshow[0]->GetUp()		* a_DT * moveSpeed;
 
 	if( GetAsyncKeyState( VK_RIGHT ) )	m_F16Flightshow[0]->GetPan()	-= 1			* a_DT * rotSpeed;
 	if( GetAsyncKeyState( VK_LEFT ) )	m_F16Flightshow[0]->GetPan()	+= 1			* a_DT * rotSpeed;

  	SceneManager::Get()->GetScene()->GetInsetCamera()->SetPosition(m_F16Flightshow[0]->GetPosition() + vector3(0, 0.1, 0));
  	SceneManager::Get()->GetScene()->GetInsetCamera()->SetPan(m_F16Flightshow[0]->GetPan());
  	SceneManager::Get()->GetScene()->GetInsetCamera()->SetTilt(m_F16Flightshow[0]->GetTilt());

	SceneManager::Get()->GetScene()->GetCamera()->Lookat(m_F16Flightshow[0]->GetPosition());

	if(GetAsyncKeyState('0')) 
	{
		m_MainTarget->SetShading(0);
		m_InsetTarget->SetShading(0);
	}
	else if(GetAsyncKeyState('1')) 
	{
		m_MainTarget->SetShading(1);
		m_InsetTarget->SetShading(1);
	}
	else if(GetAsyncKeyState('2')) 
	{
		m_MainTarget->SetShading(2);
		m_InsetTarget->SetShading(2);
	}

	// set the current rendertarget to be drawn to
	Core::Get()->SetRenderTarget(m_MainTarget);
	// clear it
	m_MainTarget->Clear();
	// set the active camera from which we need to render
	SceneManager::Get()->GetScene()->SetActiveCamera(1);
	// update the camera
	SceneManager::Get()->GetScene()->GetActiveCamera()->Update(a_DT);
	// render the scene
	SceneManager::Get()->GetScene()->Render();
	// copy the buffer to the main screen
	m_MainTarget->GetBuffer()->CopyTo(m_Surface, 0, 0);

	// same as above, except for the other camera
   	Core::Get()->SetRenderTarget(m_InsetTarget);
   	m_InsetTarget->Clear();
   	SceneManager::Get()->GetScene()->SetActiveCamera(2);
   	SceneManager::Get()->GetScene()->GetActiveCamera()->Update(a_DT);
   	SceneManager::Get()->GetScene()->Render();
   	m_InsetTarget->GetBuffer()->CopyTo(m_Surface, 0, 0);

	m_Surface->Print("Press 0, 1 or 2 to change shading", 259, 5, 0xffffff);
	char msg[256];
	sprintf_s(msg, "Polycount: %d", SceneManager::Get()->GetScene()->GetPolyCount());
	m_Surface->Print(msg, 259, 15, 0xffffff);
	m_Surface->Print("Left and right arrow to turn", 259, 25, 0xffffff);
	m_Surface->Print("W and S to move back and forth", 259, 35, 0xffffff);
	m_Surface->Print("R and F to move up and down", 259, 45, 0xffffff);
}

void Game::MouseMove( unsigned int x, unsigned int y )
{
	m_MousePosition.x = x;
	m_MousePosition.y = y;
}

void Tmpl8::Game::Delete()
{
	delete m_MainTarget;
	delete m_InsetTarget;
	for(unsigned int i = 0; i < 3; ++i)
	{
		delete m_F16Flightshow[i];
	}
	delete m_ClassicAirplane;
	delete m_Normandy;
	delete m_LegoCar;
	delete m_Scene;
	SceneManager::Get()->Delete();
}