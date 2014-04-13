#include "TextureManager.h"
#include "surface.h"

Tmpl8::TextureManager::TextureManager()
{
	// clear the containers and add an empty texture, this doesn't actually do something, but the idea was to have a default texture/mat for missing stuff
	m_Texlist.clear();
	m_TexMap.clear();
	m_Texlist.push_back(0);
	// but then I took a laziness to the brain
}

Tmpl8::TextureManager::~TextureManager()
{
	Release();
}

Tmpl8::Surface* Tmpl8::TextureManager::LoadTexture( std::string a_FileName )
{
	// Load a texture (which is just a surface) based on the name
	// return it if it already exists
	if(m_TexMap.count(a_FileName) > 0)
		return m_Texlist[m_TexMap[a_FileName]];

	// or create a new one if it doesn't
	std::string folder = "Data/";

	m_Texlist.push_back( new Surface((char*)(folder + a_FileName).c_str()));
	m_TexMap[a_FileName] = m_Texlist.size() - 1;
	
	return m_Texlist.back();
}

Tmpl8::Surface* Tmpl8::TextureManager::GetTexture( std::string a_TexName )
{
	// get the texture based on its name
	if( m_TexMap.count( a_TexName ) > 0 )
		return m_Texlist[m_TexMap[a_TexName]];

	// or make one, whatever..
	return LoadTexture( a_TexName );
}

Tmpl8::Surface* Tmpl8::TextureManager::GetTexture( unsigned int a_ID )
{
	// get texture by its ID
	return ( a_ID < 0 || a_ID >= m_Texlist.size() || m_Texlist.size() == 0 ) ? 0 : m_Texlist[a_ID];
}

int Tmpl8::TextureManager::GetTextureID( std::string a_TexName )
{
	// get the ID by the name
	return m_TexMap[a_TexName];
}

void Tmpl8::TextureManager::Release()
{
	// Delete ALL the textures \o.
	Surface* t;
	for(unsigned int i = 0; i < m_Texlist.size(); i++)
	{
		t = m_Texlist[i];
		if(t) delete t;
	}

	m_Texlist.clear();
	m_TexMap.clear();
}