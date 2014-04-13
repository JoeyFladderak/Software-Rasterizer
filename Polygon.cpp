#include "Polygon.h"

Tmpl8::Poly::Poly( int a_Data[9] )
{
	m_Vertices[0] = a_Data[0];
	m_Vertices[1] = a_Data[3];
	m_Vertices[2] = a_Data[6];

	m_Normals[0] = a_Data[2];
	m_Normals[1] = a_Data[5];
	m_Normals[2] = a_Data[8];

	m_UVs[0] = a_Data[1];
	m_UVs[1] = a_Data[4];
	m_UVs[2] = a_Data[7];

	m_Material = 0;
}

Tmpl8::Poly::~Poly()
{

}