#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <string>
#include "template.h"
#include "Polygon.h"
#include "Core.h"

namespace Tmpl8
{
	class Mesh
	{
	public:
		
		Mesh(std::string a_FileName, std::string a_Name);
		~Mesh();

		void Render();
		void Transform(matrix& a_Matrix);
		void Scale(float a_Scale);

	private:

		bool LoadOBJ( std::string a_FileName);
		
		std::string m_Name;
		std::vector<vector2> m_UV;
		std::vector<vector3> m_Vert;
		std::vector<vector3> m_OriginalVert;
		std::vector<vector3> m_Normal;
		std::vector<vector3> m_OriginalNormal;
		std::vector<Poly> m_Face;

	};
}

#endif
