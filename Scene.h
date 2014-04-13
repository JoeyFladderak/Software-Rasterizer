#ifndef _SCENE_H_
#define _SCENE_H_

#include "Camera.h"
#include "Scenegraph.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "MaterialManager.h"

namespace Tmpl8
{
	class Scene
	{
	public:
		
		Scene();
		~Scene();

		void Init();
		void Render();

		Node*				GetRootNode()		{return m_Root;}
		Camera*				GetCamera()			{return m_Camera;}
		Camera*				GetInsetCamera()	{return m_InsetCamera;}

		Camera*				GetActiveCamera();
		void				SetActiveCamera(unsigned int a_ID);

		MeshManager*		GetMeshManager()	{return m_MeshManager;}
		TextureManager*		GetTextureManager()	{return m_TextureManager;}
		MaterialManager*	GetMaterialManager(){return m_MaterialManager;}

		unsigned int		GetPolyCount()		{return m_Polycount;}
		void				SetPolyCount(unsigned int a_Amount)	{m_Polycount = a_Amount;}

	protected:

 		Node*				m_Root;
 		Camera*				m_Camera;
		Camera*				m_InsetCamera;
		Camera*				m_ActiveCamera;
 		MeshManager*		m_MeshManager;
 		TextureManager*		m_TextureManager;
 		MaterialManager*	m_MaterialManager;

		unsigned int		m_Polycount;

		unsigned int		m_CameraID;

	};
}

#endif
