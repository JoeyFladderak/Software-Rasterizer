#ifndef _MESHMANAGER_H_
#define _MESHMANAGER_H_

#include <vector>
#include <map>
#include <string>

namespace Tmpl8
{
	class Mesh;
	class MeshManager
	{
	public:
		
		MeshManager();
		~MeshManager();	

		void Release();

		Mesh* LoadMesh(std::string a_FileName, std::string a_Name);
		Mesh* GetMesh(std::string a_Name);
		Mesh* GetMesh(unsigned int a_ID);
		int GetMeshID(std::string a_Name);

	private:

		std::vector<Mesh*> m_MeshList;
		std::map<std::string, unsigned int> m_MeshMap;

	};
}

#endif
