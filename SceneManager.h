#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "template.h"
#include "Scene.h"

namespace Tmpl8
{
	class SceneManager
	{
	public:
		
		virtual ~SceneManager();	
		static SceneManager* Create();
		static SceneManager* Get() {return m_SceneManager;}
		void Delete();

		Scene* GetScene() {return m_Scene;}

	private:

		SceneManager();

		Scene* m_Scene;
		static SceneManager* m_SceneManager;

	};
}

#endif