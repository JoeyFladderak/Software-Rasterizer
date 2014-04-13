#include "Camera.h"
#include <windows.h>
#include <cmath>

Tmpl8::Camera::Camera(bool a_LookAt)
{
	// Honestly, I got this camera class from an older project and for that project I got it elsewhere but for some reason never stated the source and
	// I don't really know where I got it from anymore. I think it was from one of my classmates, but I really don't know anymore.
	Init(a_LookAt);
}

Tmpl8::Camera::~Camera()
{
}

void Tmpl8::Camera::Init(bool a_LookAt)
{
	m_Pan = 0;
	m_Tilt = 0;
	m_Roll = 0;
	m_Pos = vector3( 0, 0, 0 );
	m_OriginalPos = m_Pos;
	m_ZNear = 0.1f;
	m_ZFar = 100000.0f;
	m_Mat.Identity();
	m_MatInv = m_Mat; 
	m_MatInv.Invert();
	m_LookAt = a_LookAt;
}

void Tmpl8::Camera::Update( float a_DT )
{
	if(!m_LookAt)
	{
		float A = cos( ToRad( m_Tilt ) );
		float B = sin( ToRad( m_Tilt ) );
		float C = cos( ToRad( m_Pan ) );
		float D = sin( ToRad( m_Pan ) );
		float E = cos( ToRad( m_Roll ) );
		float F = sin( ToRad( m_Roll ) );

		float AD = A * D;
		float BD = B * D;

		m_Mat.cell[ 0] =  C * E;
		m_Mat.cell[ 1] = -C * F;
		m_Mat.cell[ 2] = -D;
		m_Mat.cell[ 3] = m_Pos.x;

		m_Mat.cell[ 4] = -BD * E + A * F;
		m_Mat.cell[ 5] =  BD * F + A * E;
		m_Mat.cell[ 6] = -B * C;
		m_Mat.cell[ 7] = m_Pos.y;

		m_Mat.cell[ 8] =  AD * E + B * F;
		m_Mat.cell[ 9] = -AD * F + B * E;
		m_Mat.cell[10] =  A * C;
		m_Mat.cell[11] = m_Pos.z;

		m_Mat.cell[12] = 0;
		m_Mat.cell[13] = 0;
		m_Mat.cell[14] = 0;
		m_Mat.cell[15] = 1;

		m_MatInv = m_Mat;
		m_MatInv.Invert();

		m_Up = vector3( m_Mat.cell[1], m_Mat.cell[5], m_Mat.cell[9] );
		m_Side = vector3( m_Mat.cell[0], m_Mat.cell[4], m_Mat.cell[8] );
		m_Forward = vector3( m_Mat.cell[2], m_Mat.cell[6], m_Mat.cell[10] );
	}
}

void Tmpl8::Camera::Lookat( const vector3& a_Target )
{
	vector3 f = (a_Target - m_Pos).Normalized();
	vector3 u = vector3(0, 1, 0).Normalized();
	vector3 s = f.Cross(u).Normalized();
	u = s.Cross(f);

	m_Mat.cell[0] = -s.x;
	m_Mat.cell[4] = -s.y;
	m_Mat.cell[8] = -s.z;

	m_Mat.cell[1] = u.x;
	m_Mat.cell[5] = u.y;
	m_Mat.cell[9] = u.z;

	m_Mat.cell[2] = f.x;
	m_Mat.cell[6] = f.y;
	m_Mat.cell[10] = f.z;

 	m_Mat.cell[3] = m_Pos.x;
 	m_Mat.cell[7] = m_Pos.y;
 	m_Mat.cell[11] = m_Pos.z;
}
