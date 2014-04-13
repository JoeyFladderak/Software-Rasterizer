#include "MeshManager.h"
#include "Mesh.h"

Tmpl8::MeshManager::MeshManager()
{

}

Tmpl8::MeshManager::~MeshManager()
{
	Release();
}

Tmpl8::Mesh* Tmpl8::MeshManager::LoadMesh( std::string a_FileName, std::string a_Name )
{
	// Loads a mesh and returns an existing mesh or..
	if(m_MeshMap.count(a_Name) > 0)
		return m_MeshList[m_MeshMap[a_Name]];

	// .. Create a new mesh and return that one
	m_MeshList.push_back(new Mesh(a_FileName, a_Name));
	m_MeshMap[a_Name] = m_MeshList.size() - 1;
	return m_MeshList.back();
}

Tmpl8::Mesh* Tmpl8::MeshManager::GetMesh( std::string a_Name )
{
	// Return a mesh based on its name
	if(m_MeshMap.count(a_Name) > 0)
		return m_MeshList[m_MeshMap[a_Name]];

	// or create a new mesh on the based name
	return LoadMesh(a_Name, a_Name);
}

Tmpl8::Mesh* Tmpl8::MeshManager::GetMesh( unsigned int a_ID )
{
	// Return a mesh by its ID
	return ( a_ID < 0 || a_ID >= m_MeshList.size() || m_MeshList.size() == 0 ) ? 0 : m_MeshList[a_ID];
}

int Tmpl8::MeshManager::GetMeshID( std::string a_Name )
{
	// Return the mesh ID based on the given name
	return m_MeshMap[a_Name];
}

void Tmpl8::MeshManager::Release()
{
	// Delete ALL the meshes \o.
	Mesh* m;
	for(unsigned int i = 0; i < m_MeshList.size(); i++)
	{
		m = m_MeshList[i];
		if(m) delete m;
	}

	m_MeshList.clear();
	m_MeshMap.clear();
}