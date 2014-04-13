#include "SceneManager.h"

Tmpl8::SceneManager* Tmpl8::SceneManager::m_SceneManager = NULL;

Tmpl8::SceneManager::SceneManager()
{
	// I wanted to support multiple scenes, but then I took an arrow to the knee
	m_Scene = new Scene();
	m_Scene->Init();
}

Tmpl8::SceneManager* Tmpl8::SceneManager::Create()
{
	if(!m_SceneManager)
	{
		m_SceneManager = new Tmpl8::SceneManager();
	}

	return m_SceneManager;
}

Tmpl8::SceneManager::~SceneManager()
{

}

void Tmpl8::SceneManager::Delete()
{
	if(m_Scene)
		delete m_Scene;
}
