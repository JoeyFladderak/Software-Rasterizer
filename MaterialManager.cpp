#include "MaterialManager.h"
#include "Material.h"
#include "SceneManager.h"

Tmpl8::MaterialManager::MaterialManager()
{
	// Clear the vector and map and add a default material
	m_Matlist.clear();
	m_MatMap.clear();
	m_Matlist.push_back(new Material());
}

Tmpl8::MaterialManager::~MaterialManager()
{
	Release();
}

void Tmpl8::MaterialManager::LoadMaterials( std::string a_FileName )
{
	// open the file for reading (folder string added to point to the data folder where assets are stored)
	FILE* file = NULL;
	std::string folder = "Data/";
	
	fopen_s(&file, (folder + a_FileName).c_str(), "r");
	
	if(!file)
		return;

	char line[256];
	Material* material = NULL;
	char val[256];
	while(fgets( line, 255, file ))
	{
		if( !strncmp(line, "newmtl ", 7))
		{
			// Create a new material or use one if it already exists
			sscanf(line + 7, "%s", val);
			if(m_MatMap.count(val) > 0)
			{
				material = m_Matlist[m_MatMap[val]];
			}
			else
			{
				material = new Material();
				m_Matlist.push_back(material);
				m_MatMap[val] = m_Matlist.size() - 1;
				material->SetName(val);
				material->SetID(GetMaterialID(val));
			}
		}

		// Write away the ambient values
		if(!strncmp(line, "Ka ", 3))
			sscanf(line + 3, "%f %f %f", &material->GetAmbient().r, &material->GetAmbient().g, &material->GetAmbient().b);

		// Write away the diffuse values
		if(!strncmp(line, "Kd ", 3))
			sscanf(line + 3, "%f %f %f", &material->GetDiffuse().r, &material->GetDiffuse().g, &material->GetDiffuse().b);

		// Write away the specular values
		if(!strncmp(line, "Ks ", 3))
			sscanf(line + 3, "%f %f %f", &material->GetSpecular().r, &material->GetSpecular().g, &material->GetSpecular().b);

		// Write away the emissive values
		if(!strncmp(line, "Em ", 3))
			sscanf(line + 3, "%f %f %f", &material->GetEmissive().r, &material->GetEmissive().g, &material->GetEmissive().b);

		// Write away the shininess values
		if(!strncmp( line, "Ns ", 3))
			sscanf(line + 3, "%f", &material->GetShininess() );

		// Write away the diffusemap (texture) values
		if( !strncmp( line, "map_Kd ", 7 ) )
		{
			if( strlen( line ) > 9 )
			{
				sscanf( line + 7, "%s", val );
				SceneManager::Get()->GetScene()->GetTextureManager()->LoadTexture( val );
				material->SetDiffuseMap(SceneManager::Get()->GetScene()->GetTextureManager()->GetTextureID(val));
			}
		}
	}

	fclose(file);
}

Tmpl8::Material* Tmpl8::MaterialManager::GetMaterial( std::string a_MatName )
{
	// return material based on the name
	return ( m_MatMap.count( a_MatName ) > 0 ) ? m_Matlist[m_MatMap[a_MatName]] : 0;
}

Tmpl8::Material* Tmpl8::MaterialManager::GetMaterial( unsigned int a_ID )
{
	// return material based on ID
	return ( a_ID < 0 || a_ID >= m_Matlist.size() || m_Matlist.size() == 0 ) ? 0 : m_Matlist[a_ID];
}

int Tmpl8::MaterialManager::GetMaterialID( std::string a_MatName )
{
	// return the ID of a material based on its name
	return m_MatMap[a_MatName];
}

void Tmpl8::MaterialManager::Release()
{
	// Delete ALL the materials \o.
 	Material *m;
 	for( unsigned int i = 0; i < m_Matlist.size(); i++ )
 	{
 		m = m_Matlist[i];
 		if( m ) delete m;
 	}
 	m_Matlist.clear();
 	m_MatMap.clear();
}