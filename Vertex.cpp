#include "Vertex.h"
#include "Core.h"

Tmpl8::Vertex::Vertex( vector3 a_Vertex, vector3 a_Normal, vector2 a_UV )
{
	// Vertex constructer that applies all the needed transforms, perspective and such
	m_Vertex = a_Vertex + vector3(Core::Get()->GetRenderTarger()->GetBuffer()->GetWidth() >> 1, Core::Get()->GetRenderTarger()->GetBuffer()->GetHeight() >> 1, 0);
	m_Normal = a_Normal;
	m_UV = a_UV;

	m_VertexTransformed.z = 1.0f / (a_Vertex.z * 0.003f);
	m_VertexTransformed.x = (a_Vertex.x * m_VertexTransformed.z) + (Core::Get()->GetRenderTarger()->GetBuffer()->GetWidth() >> 1);
	m_VertexTransformed.y = (a_Vertex.y * m_VertexTransformed.z) + (Core::Get()->GetRenderTarger()->GetBuffer()->GetHeight() >> 1);

	m_NormalTransformed = a_Normal * m_VertexTransformed.z;
	m_UVTransformed = a_UV * m_VertexTransformed.z;
}

Tmpl8::Vertex::Vertex()
{

}

Tmpl8::Vertex::~Vertex()
{

}
