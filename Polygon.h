#ifndef _POLYGON_H
#define _POLYGON_H

namespace Tmpl8
{
	class Poly
	{
	public:

		Poly(int a_Data[9]);
		~Poly();

		const int GetVertice(int a_Index) const {return m_Vertices[a_Index];}
		const int GetNormal(int a_Index) const {return m_Normals[a_Index];}
		const int getUV(int a_Index) const {return m_UVs[a_Index];}
		const int GetMaterial() const {return m_Material;}

		void SetMaterial(const int a_Material) {m_Material = a_Material;}

	private:

		int m_Vertices[3];
		int m_Normals[3];
		int m_UVs[3];
		int m_Material;

	};
};

#endif