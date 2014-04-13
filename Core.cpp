#include "Core.h"

Tmpl8::Core* Tmpl8::Core::m_Core = NULL;

Tmpl8::Core::Core()
{
	m_CurrentRenderTarget = NULL;
}

Tmpl8::Core* Tmpl8::Core::Create()
{
	if(!m_Core)
	{
		m_Core = new Tmpl8::Core();
	}

	return m_Core;
}

void Tmpl8::Core::DrawTriangle( const Vertex& a_V1, const Vertex& a_V2, const Vertex& a_V3)
{
	// temp values for boundaries checking
	vector3 v1 = a_V1.GetTransformedVertex();
	vector3 v2 = a_V2.GetTransformedVertex();
	vector3 v3 = a_V3.GetTransformedVertex();

	// by default, they're in.. because I say so
	bool InWidth = true;
	bool inHeight = true;
	bool inDepth = true;

	// in between the left and right of the screen?
  	if(v1.x < 0 && v2.x < 0 && v3.x < 0 || v1.x > m_CurrentRenderTarget->GetWidth() && v2.x > m_CurrentRenderTarget->GetWidth() && v3.x > m_CurrentRenderTarget->GetWidth())
  		InWidth = false;
  
	// in between the bottom and top of the screen?
  	if(v1.y < 0 && v2.y < 0 && v3.y < 0 || v1.y > m_CurrentRenderTarget->GetHeight() && v2.y > m_CurrentRenderTarget->GetHeight() && v3.y > m_CurrentRenderTarget->GetHeight())
  		inHeight = false;

	// if we are inside the screen
	if(InWidth && inHeight)
	{
		// We may draw the triangle!
		float zMin = SceneManager::Get()->GetScene()->GetCamera()->GetZNear();
		// some near Z checking first, you never know eh?
		// Cheap trick
		int z0 = v1.z > zMin ? 1 : 0;
		int z1 = v2.z > zMin ? 1 : 0;
		int z2 = v3.z > zMin ? 1 : 0;
		int z0z1z2 = z0 + z1 + z2;
		
		// if we pass this, everything is in screen and we can go on and draw the triangle
		if( z0z1z2 == 3 )
			m_CurrentRenderTarget->DrawTriangle(a_V1, a_V2, a_V3);
	}
}

Tmpl8::Pixel Tmpl8::Core::GetUVColor( float a_U, float a_V )
{
	// speaks for itself, get the color from the texture to draw
	a_U = a_U > 0 ? a_U - (int)a_U : ( 1.f + a_U ) - (int)a_U;
	a_V = a_V > 0 ? a_V - (int)a_V : ( 1.f + a_V ) - (int)a_V;

	a_V = 1.f - a_V;

	int u = (int)(a_U * m_Texture->GetWidth());
	int v = (int)(a_V * m_Texture->GetHeight());

	if( m_Texture->GetWidth() == 0 || m_Texture->GetHeight() == 0 ) return 0xffffff;
	u = CLAMP( u, 0, m_Texture->GetWidth() - 1 );
	v = CLAMP( v, 0, m_Texture->GetHeight() - 1 );

	return m_Texture->GetBuffer()[u + v * m_Texture->GetPitch()];
}

Tmpl8::Core::~Core()
{

}

Tmpl8::Color Tmpl8::Core::SetShading( const vector3& a_WorldPos, const vector3& a_Normal, const vector2& a_UV, int a_ShadingType )
{
 	Color tempcol;
 	vector3 light = SceneManager::Get()->GetScene()->GetInsetCamera()->GetMatrixInv().Transform(vector3(100, 100, -1000));
 	Color diffuse = Color(0.8f, 0.8f, 0.8f);
 	Color specular = Color(0.8f, 0.8f, 0.8f);
 	Color ambient = Color(0.2f, 0.2f, 0.2f);
 	vector3 position = SceneManager::Get()->GetScene()->GetInsetCamera()->GetPosition();

	if(a_ShadingType == 1)
	{
	  	Color texcol = m_Texture ? tempcol.FromPixel(GetUVColor(a_UV.u, a_UV.v)) : GetColor();
	  	vector3 L = (light - a_WorldPos).Normalized();
	  	vector3 N = a_Normal;
	  	N.Normalize();
	  	vector3 V = position - a_WorldPos;
	  	float dst = 1.0f / DOT(V, V);
	  	vector3 H = (L + V).Normalized();
	  
	  	float diff = 0.25f * DOT(N, L);
	  	float spec = 0.8f * powf(DOT(N, H), 32);
	  
	  	Color tmpcol;
	  	tmpcol += diff * (diffuse * texcol);
	  	tmpcol += spec * (specular * texcol);
	  	tmpcol += ambient * texcol;
	  	return tmpcol;
	}
	else if(a_ShadingType == 2)
 	{
 		Color texcol = m_Texture ? tempcol.FromPixel(GetUVColor(a_UV.u, a_UV.v)) : GetColor();
 		vector3 L = (light - a_WorldPos).Normalized();
 		vector3 N = a_Normal;
 		N.Normalize();
 		vector3 V = position - a_WorldPos;
 		float dst = 1.0f / DOT(V, V);
 		float diff = DOT(N, L);
 
 		diff = CLAMP(diff, 0.01f, 1.0f);
 
 		Color tmpcol;
 		tmpcol += diff * (diffuse * texcol);
 		tmpcol += ambient * texcol;
 		return tmpcol;
 	}
}