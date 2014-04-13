#include "Scene.h"

void Tmpl8::Scene::Init()
{
	// So this scene contains:
	// the static camera
	m_Camera = new Tmpl8::Camera(true);
	// the camera that follows the plane
	m_InsetCamera = new Tmpl8::Camera(false);
	// the root node
	m_Root = new Tmpl8::Node();
	// the manager that contains all the meshes
	m_MeshManager = new Tmpl8::MeshManager();
	// the manager that contains all the textures
	m_TextureManager = new Tmpl8::TextureManager();
	// the manager that contains.. can you guess it?
	m_MaterialManager = new Tmpl8::MaterialManager();

	// stuff
	m_ActiveCamera = m_Camera;

	// we got more cameras, set the current one
	m_CameraID = 1;

	// amount of polygons
	m_Polycount = 0;
}

void Tmpl8::Scene::Render()
{
	if(m_Root)
		m_Root->Render();
}

Tmpl8::Scene::Scene()
{

}

Tmpl8::Scene::~Scene()
{
	delete m_Camera;
	delete m_InsetCamera;
	delete m_Root;
	delete m_MeshManager;
	delete m_TextureManager;
	delete m_MaterialManager;
}

Tmpl8::Camera* Tmpl8::Scene::GetActiveCamera()
{
	// return whichever camera is currently active.
	return m_ActiveCamera;
}

void Tmpl8::Scene::SetActiveCamera(unsigned int a_ID)
{
	// switch between cameras, needed for rendering
	if(a_ID == 1)
	{
		m_ActiveCamera = m_Camera;
	}
	if (a_ID == 2)
	{
		m_ActiveCamera = m_InsetCamera;
	}
}