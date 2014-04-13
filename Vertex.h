#ifndef _VERTEX_H
#define _VERTEX_H

#include "template.h"

namespace Tmpl8
{
	class Vertex
	{
	public:

		Vertex(vector3 a_Vertex, vector3 a_Normal, vector2 a_UV);
		Vertex();
		~Vertex();

		const vector3& GetVertex()	const {return m_Vertex;}
		const vector3& GetNormal()	const {return m_Normal;}
		const vector2& GetUV()		const {return m_UV;}

		void SetVertex(const vector3& a_Vertex)	{m_Vertex = a_Vertex;}
		void SetNormal(const vector3& a_Normal)	{m_Normal = a_Normal;}
		void SetUV(const vector2& a_UV)			{m_UV = a_UV;}

		const vector3& GetTransformedVertex()	const {return m_VertexTransformed;}
		const vector3& GeTransformedtNormal()	const {return m_NormalTransformed;}
		const vector2& GetTransformedUV()		const {return m_UVTransformed;}

		void SetTransformedVertex(const vector3& a_VertexTransformed)	{m_VertexTransformed = a_VertexTransformed;}
		void SetTransformedNormal(const vector3& a_NormalTransformed)	{m_NormalTransformed = a_NormalTransformed;}
		void SetTransformedUV(const vector2& a_UVTransformed)			{m_UVTransformed = a_UVTransformed;}

	private:

		vector3	m_Vertex;
		vector3 m_Normal;
		vector2 m_UV;

		vector3 m_VertexTransformed;
		vector3 m_NormalTransformed;
		vector2 m_UVTransformed;
	};
};

#endif