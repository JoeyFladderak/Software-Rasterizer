#ifndef _MATERIALMANAGER_H
#define _MATERIALMANAGER_H

#include <vector>
#include <map>
#include <string>

namespace Tmpl8
{
	class Material;
	class MaterialManager
	{
	public:

		MaterialManager();
		~MaterialManager();

		void Release();

		void LoadMaterials( std::string a_FileName);

		Material* GetMaterial(std::string a_MatName);
		Material* GetMaterial(unsigned int a_ID);

		int GetMaterialID( std::string a_MatName);

	private:

		std::vector<Material*> m_Matlist;
		std::map<std::string, unsigned int> m_MatMap;

	};
};

#endif