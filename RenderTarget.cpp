#include "RenderTarget.h"

Tmpl8::RenderTarget::RenderTarget( unsigned int a_Width, unsigned int a_Height)
{
	// setting stuff up
	m_CurrentShading = 0;
	m_Width = a_Width;
	m_Height = a_Height;
	m_Buffer = new Surface(m_Width, a_Height);
	m_SpanMax = new Span[m_Height];
	m_SpanMin = new Span[m_Height];
	m_ZBuffer = new float[m_Width * m_Height];

	for( unsigned int i = 0; i < m_Height; i++ ) 
		ResetSpanLine( i );

	Clear();
}

void Tmpl8::RenderTarget::DrawTriangle( const Vertex& a_V1, const Vertex& a_V2, const Vertex& a_V3)
{
	ScanEdge(a_V1, a_V2);
	ScanEdge(a_V2, a_V3);
	ScanEdge(a_V3, a_V1);

	int y1 = (int)MIN( a_V1.GetTransformedVertex().y, MIN( a_V2.GetTransformedVertex().y, a_V3.GetTransformedVertex().y ) );
	int y2 = (int)MAX( a_V1.GetTransformedVertex().y, MAX( a_V2.GetTransformedVertex().y, a_V3.GetTransformedVertex().y ) );

	float t_x, t_y, t_z, t_u, t_v, t_nx, t_ny, t_nz;

	// Now this is a story of a little triangle that wanted nothing more than to be a colorfull little thing
	for( int y = y1; y <= y2; y++ )
	{
		if( ( y < m_Buffer->GetHeight() ) && ( y >= 0 ) && ( m_SpanMin[y].GetVertX() < m_SpanMax[y].GetVertX() ) )
		{
			int yw = y * m_Buffer->GetWidth();
			// It had some starting values, but that wasn't enough yet!
			float z = m_SpanMin[y].GetVertZ();
			float u = m_SpanMin[y].GetU();
			float v = m_SpanMin[y].GetV();
			float nx = m_SpanMin[y].GetNormalX();
			float ny = m_SpanMin[y].GetNormalY();
			float nz = m_SpanMin[y].GetNormalZ();
			// It decided to check its entire body, where each color should come
			float dx = 1.f / ( m_SpanMax[y].GetVertX() - m_SpanMin[y].GetVertX() );
			float dz = ( m_SpanMax[y].GetVertZ() - m_SpanMin[y].GetVertZ() ) * dx;
			float du = ( m_SpanMax[y].GetU() - m_SpanMin[y].GetU() ) * dx;
			float dv = ( m_SpanMax[y].GetV() - m_SpanMin[y].GetV() ) * dx;
			float dnx = ( m_SpanMax[y].GetNormalX() - m_SpanMin[y].GetNormalX() ) * dx;
			float dny = ( m_SpanMax[y].GetNormalY() - m_SpanMin[y].GetNormalY() ) * dx;
			float dnz = ( m_SpanMax[y].GetNormalZ() - m_SpanMin[y].GetNormalZ() ) * dx;
			// And when the timing was right..
			for( int x = (int)m_SpanMin[y].GetVertX(); x < (int)m_SpanMax[y].GetVertX(); x++ )
			{
				if( x >= m_Buffer->GetWidth() ) break;
				if( x < 0 )
				{
					const int minx = -x;
					z += dz * minx;
					u += du * minx;
					v += dv * minx;
					nx += dnx * minx;
					ny += dny * minx;
					nz += dnz * minx;
					x = 0;
				}
				if( z > m_ZBuffer[x+yw] )
				{
					m_ZBuffer[x+yw] = z;
					t_z = 1.f / z;
					t_x = x * t_z;
					t_y = y * t_z;
					t_u = u * t_z;
					t_v = v * t_z;
					t_nx = nx * t_z;
					t_ny = ny * t_z;
					t_nz = nz * t_z;
					Pixel color;

					if (m_CurrentShading == 1)
					{
						color = Core::Get()->SetShading(vector3(t_x, t_y, t_z), vector3(t_nx, t_ny, t_nz), vector2(t_u, t_v), m_CurrentShading).ToPixel();
	 					Color col;
 						col.FromPixel(color);
					}
					else if (m_CurrentShading == 2)
					{
						color = Core::Get()->SetShading(vector3(t_x, t_y, t_z), vector3(t_nx, t_ny, t_nz), vector2(t_u, t_v), m_CurrentShading).ToPixel();
						Color col;
						col.FromPixel(color);
					}
					else if(m_CurrentShading == 0)
						color = Core::Get()->GetTexture() ? Core::Get()->GetUVColor(t_u, t_v) : Core::Get()->GetColor().ToPixel();
					
					m_Buffer->Plot( x, m_Buffer->GetHeight() - y, color );
				} 
				z += dz;
				u += du;
				v += dv;
				nx += dnx;
				ny += dny;
				nz += dnz;
			}
		} 
		// it became a colorfull little triangle
		ResetSpanLine( y );
	} 

}

void Tmpl8::RenderTarget::ScanEdge( const Vertex& a_V1, const Vertex& a_V2 )
{
	Tmpl8::Vertex v1 = a_V1;
	Tmpl8::Vertex v2 = a_V2;

	if(v1.GetTransformedVertex().y > v2.GetTransformedVertex().y)
		return ScanEdge(v2, v1);

	const vector3 deltaV = v2.GetTransformedVertex() - v1.GetTransformedVertex();
	const vector3 deltaN = v2.GeTransformedtNormal() - v1.GeTransformedtNormal();
	const vector2 deltaUV = v2.GetTransformedUV() - v1.GetTransformedUV();

	float inv_dy = deltaV.y == 0 ? 0 : 1.f / deltaV.y;
	int y1 = (int)v1.GetTransformedVertex().y, y2 = (int)v2.GetTransformedVertex().y;

	float x = v1.GetTransformedVertex().x;
	float z = v1.GetTransformedVertex().z;
	float nx = v1.GeTransformedtNormal().x;
	float ny = v1.GeTransformedtNormal().y;
	float nz = v1.GeTransformedtNormal().z;
	float u = v1.GetTransformedUV().u;
	float v = v1.GetTransformedUV().v;

	float dx = deltaV.x * inv_dy;
	float dz = deltaV.z * inv_dy;
	float dnx = deltaN.x * inv_dy;
	float dny = deltaN.y * inv_dy;
	float dnz = deltaN.z * inv_dy;
	float du = deltaUV.u * inv_dy;
	float dv = deltaUV.v * inv_dy;

	float inc = 1.0f - ((v1.GetTransformedVertex().y)-((int)(v1.GetTransformedVertex().y)));

	// subpixel/texel correction thingies
	y1++;
	x += dx * inc;
	z += dz * inc;
	nx += dnx * inc;
	ny += dny * inc;
	nz += dnz * inc;
	u += du * inc;
	v += dv * inc;

	for( int y = y1; y <= y2; y++ )
	{
		if( y >= 0 && y < m_Buffer->GetHeight() && z > 0 )
		{
			if( x < m_SpanMin[y].GetVertX() )
			{
				m_SpanMin[y].SetVertX(((int)x) + 1);
				m_SpanMin[y].SetVertY((float)y);
				m_SpanMin[y].SetVertZ(z);
				m_SpanMin[y].SetNormalX(nx);
				m_SpanMin[y].SetNormalY(ny);
				m_SpanMin[y].SetNormalZ(nz);
				m_SpanMin[y].SetU(u);
				m_SpanMin[y].SetV(v);
			}
			if( x > m_SpanMax[y].GetVertX() )
			{
				m_SpanMax[y].SetVertX(((int)x) + 1);
				m_SpanMax[y].SetVertY((float)y);
				m_SpanMax[y].SetVertZ(z);
				m_SpanMax[y].SetNormalX(nx);
				m_SpanMax[y].SetNormalY(ny);
				m_SpanMax[y].SetNormalZ(nz);
				m_SpanMax[y].SetU(u);
				m_SpanMax[y].SetV(v);
			}
		}
		x += dx;
		z += dz;
		nx += dnx;
		ny += dny;
		nz += dnz;
		u += du;
		v += dv;
	}
}

void Tmpl8::RenderTarget::ResetSpanLine( int line )
{
	if( line < 0 || line >= m_Buffer->GetHeight() )
		return;

	m_SpanMax[line].SetVertX(0);
	m_SpanMin[line].SetVertX((float)m_Buffer->GetWidth() - 1);
}

void Tmpl8::RenderTarget::Clear()
{
	m_Buffer->Clear(0x111111);

	if( m_ZBuffer )
	{
		for( int i = 0; i < m_Buffer->GetWidth() * m_Buffer->GetHeight(); i++ )
		{
			m_ZBuffer[i] = 0;
		}
	}
}

Tmpl8::RenderTarget::~RenderTarget()
{
	delete m_Buffer;
	delete m_ZBuffer;
	delete m_SpanMax;
	delete m_SpanMin;
}
