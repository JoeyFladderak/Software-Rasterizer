 #ifndef _TEXTUREMANAGER_H
 #define _TEXTUREMANAGER_H
 
 #include <vector>
 #include <map>
 #include <string>
 
 namespace Tmpl8
 {
 	class Surface;
 	class TextureManager
 	{
 	public:
 
 		TextureManager();
 		~TextureManager();

		void Release();
 
 		Surface* LoadTexture( std::string a_FileName);
 
 		Surface* GetTexture(std::string a_TexName);
 		Surface* GetTexture(unsigned int a_ID);
 
 		int GetTextureID( std::string a_TexName);
 
 	private:
 
 		std::vector<Surface*> m_Texlist;
 		std::map<std::string, unsigned int> m_TexMap;
 
 	};
 };
 
 #endif