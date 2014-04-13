#include "Frustum.h"

Tmpl8::Frustum::Frustum()
{
////////////////////////////////// Viewspace frustum ////////////////////////////////////////
// didn't quit finish it.

 	float top = -(SCRHEIGHT / 2) + 1;
 	float left = -(SCRWIDTH / 2) + 1;
 	float bottom = (SCRHEIGHT / 2) - 1;
 	float right = (SCRWIDTH / 2) - 1;
 	float nearp = 1.0f;
 	float farp = 50;
 	float FoV = 0.003;
 
 	for(unsigned int i = 0; i < 6; ++i)
 	{
 		m_Plane[i] = new Plane();
 	}
 
 	vector3 nv1, nv2, nv3, nv4;
 	vector3 fv1, fv2, fv3, fv4;
 
 	nv1.x = left * nearp / FoV;
 	nv1.y = top * nearp / FoV;
 	nv1.z = nearp;
 
 	nv2.x = left * nearp / FoV;
 	nv2.y = bottom * nearp / FoV;
 	nv2.z = nearp;
 
 	nv3.x = right * nearp / FoV;
 	nv3.y = top * nearp / FoV;
 	nv3.z = nearp;
 
 	nv4.x = right * nearp / FoV;
 	nv4.y = bottom * nearp / FoV;
 	nv4.z = nearp;
 
 	fv1.x = left * farp / FoV;
 	fv1.y = top * farp / FoV;
 	fv1.z = farp;
 
 	fv2.x = left * farp / FoV;
 	fv2.y = bottom * farp / FoV;
 	fv2.z = farp;
 
 	fv3.x = right * farp / FoV;
 	fv3.y = top * farp / FoV;
 	fv3.z = farp;
 
 	fv4.x = right * farp / FoV;
 	fv4.y = bottom * farp / FoV;
 	fv4.z = farp;
 
 	//Left
 	vector3 edge1 = nv1 - nv2;
 	vector3 edge2 = nv1 - fv1;
 	vector3 normal = edge1.Cross(edge2);
 	float length = normal.Length();
 	normal.Normalize();
 	m_Plane[Frustum::PLANE_LEFT]->SetNormal(normal);
 	m_Plane[Frustum::PLANE_LEFT]->SetDistance(0);
 
 
 	//Right
 	edge1 = nv4 - nv3;
 	edge2 = nv3 - fv3;
 	normal = edge1.Cross(edge2);
 	normal.Normalize();
 	m_Plane[Frustum::PLANE_RIGHT]->SetNormal(normal);
 	m_Plane[Frustum::PLANE_RIGHT]->SetDistance(0);
 
 	//Top
 	edge1 = nv4 - nv2;
 	edge2 = nv2 - fv2;
 	normal = edge2.Cross(edge1);
 	normal.Normalize();
 	m_Plane[Frustum::PLANE_TOP]->SetNormal(normal);
 	m_Plane[Frustum::PLANE_TOP]->SetDistance(0);
 
 	//bottom
 	edge1 = nv3 - nv1;
 	edge2 = nv1 - fv1;
 	normal = edge1.Cross(edge2);
 	normal.Normalize();
 	m_Plane[Frustum::PLANE_BOTTOM]->SetNormal(normal);
 	m_Plane[Frustum::PLANE_BOTTOM]->SetDistance(0);
 
 	m_Plane[Frustum::PLANE_NEAR]->SetNormal(vector3(0, 0, 1));
 	m_Plane[Frustum::PLANE_NEAR]->SetDistance(nearp);
 	m_Plane[Frustum::PLANE_FAR]->SetNormal(vector3(0, 0, -1));
 	m_Plane[Frustum::PLANE_FAR]->SetDistance(-farp);
}

void Tmpl8::Frustum::UpdateFrustum( matrix& a_Mat, vector3& a_Campos )
{
	vector3 x_Axis = vector3(a_Mat.cell[0], a_Mat.cell[4], a_Mat.cell[8]);
	vector3 y_Axis = vector3(a_Mat.cell[1], a_Mat.cell[5], a_Mat.cell[9]);
	vector3 z_Axis = vector3(a_Mat.cell[2], a_Mat.cell[6], a_Mat.cell[10]);

	// lol where's the rest of the code?
}

Tmpl8::Frustum::~Frustum()
{
	for(unsigned int i = 0; i < 6; ++i)
		delete m_Plane[i];
}