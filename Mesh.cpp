#include "Mesh.h"
#include "Material.h"
#include "Vertex.h"
#include "Frustum.h"
#include "SceneManager.h"

Tmpl8::Mesh::Mesh( std::string a_FileName, std::string a_Name )
{
	m_Name = a_Name;
	LoadOBJ(a_FileName.c_str());
}

Tmpl8::Mesh::~Mesh()
{
	m_UV.clear();
	m_Vert.clear();
	m_OriginalVert.clear();
	m_Normal.clear();
	m_OriginalNormal.clear();
	m_Face.clear();
}

void Tmpl8::Mesh::Render()
{
	Poly* poly = 0;
	int materialindex = 0;
	Material* material = 0;

	Frustum* frustum = new Frustum();

	// loop through the faces of the mesh for material assignment
	for(unsigned int i = 0; i < m_Face.size(); i++)
	{
		poly = &m_Face[i];

		// Check if the material isn't already applied, if it is, continue with the current material
		if(poly->GetMaterial() != materialindex)
		{
			// We need a new material, get it here and set materialindex so it doesn't loop through the same materials
 			material = SceneManager::Get()->GetScene()->GetMaterialManager()->GetMaterial( materialindex = poly->GetMaterial() );
			// Get the texture from the current material
 			Surface* tex = SceneManager::Get()->GetScene()->GetTextureManager()->GetTexture( material->GetDiffusemapID() );
 			
			// Set the texture and color to be used for rendering.
			Core::Get()->SetTexture(tex);
			Core::Get()->SetColor(material->GetAmbient());
		}

		// Construct the 3 vertices from the poly data to be passed for rendering.
		Tmpl8::Vertex v1(m_Vert[poly->GetVertice(0)], m_Normal[poly->GetNormal(0)], m_UV[poly->getUV(0)]);
		Tmpl8::Vertex v2(m_Vert[poly->GetVertice(1)], m_Normal[poly->GetNormal(1)], m_UV[poly->getUV(1)]);
		Tmpl8::Vertex v3(m_Vert[poly->GetVertice(2)], m_Normal[poly->GetNormal(2)], m_UV[poly->getUV(2)]);

// 		// Perform backface culling before actual drawing.
// 		vector3 one = v3.GetTransformedVertex() - v2.GetTransformedVertex();
// 		vector3 two = v2.GetTransformedVertex() - v1.GetTransformedVertex();
// 
// 		vector3 norm = CROSS(one, two);
// 
// 		if(norm.z > 0.0f)
// 			Core::Get()->DrawTriangle(v1, v2, v3);

		// This was supposed to be Sutherland-hodgeman clipping, though near clipping didn't work properly and it slowed down more then it increased so disabled it.
		// Next to that I kinda destroyed my frustum and didn't back it up...

 		float dist[3];
 		bool allin = true;
 		bool allout = true;
 
     		for(unsigned int j = 0; j < 3; ++j)
     		{
     			Vertex vert(m_Vert[poly->GetVertice(j)], m_Normal[poly->GetNormal(j)], m_UV[poly->getUV(j)]);
    
    			for(unsigned int k = 0; k < 6; k++)
    			{
    				dist[j] = frustum->GetFrustumPlane(k).x * vert.GetVertex().x +
    						  frustum->GetFrustumPlane(k).y * vert.GetVertex().y +
    						  frustum->GetFrustumPlane(k).z * vert.GetVertex().z - frustum->GetFrustumDistance(k);
    
    				if(dist[j] < -0.001) allin = false;
    				if(dist[j] >= 0.001) allout = false;
    			}
    		}
 
  		if(allin)
  		{
  			vector3 one = v3.GetTransformedVertex() - v2.GetTransformedVertex();
  			vector3 two = v2.GetTransformedVertex() - v1.GetTransformedVertex();
  
  			vector3 norm = CROSS(one, two);
  
  			if(norm.z > 0.0f)
  				Core::Get()->DrawTriangle(v1, v2, v3);
 
  			continue;
  		}
  		else if(allout)
  			continue;
 
  		Vertex clippedvert[10];
  		Vertex cv1(m_Vert[poly->GetVertice(0)], m_Normal[poly->GetNormal(0)], m_UV[poly->getUV(0)]);
  		float dist2;
  		float dist1 = dist[0];
  		bool clipped = false;
  		bool inside = (dist1 >= 0);
  		int curv = 0;
  
  		for(unsigned int j = 1; j <= 3; ++j)
  		{
  			Vertex cv2(m_Vert[poly->GetVertice(j % 3)], m_Normal[poly->GetNormal(j % 3)], m_UV[poly->getUV(j % 3)]);
  			dist2 = dist[j % 3];
  
  			if(inside && (dist2 >= 0.0f))
  			{
  				clippedvert[curv++] = cv2;
  			}
  			else if((!inside) && (dist2 >= 0.001))
  			{
  				clipped = inside = true;
  				Vertex t;
  				float d = dist1 / (dist1 - dist2);
  				t.SetVertex(vector3((cv1.GetVertex().x + cv2.GetVertex().x - cv1.GetVertex().x) * d,
  									(cv1.GetVertex().y + cv2.GetVertex().y - cv1.GetVertex().y) * d,
  									(cv1.GetVertex().z + cv2.GetVertex().z - cv1.GetVertex().z) * d));
  
  				t.SetTransformedVertex(vector3((cv1.GetTransformedVertex().x + (cv2.GetTransformedVertex().x - cv1.GetTransformedVertex().x) * d),
  											   (cv1.GetTransformedVertex().y + (cv2.GetTransformedVertex().y - cv1.GetTransformedVertex().y) * d),
  											   (cv1.GetTransformedVertex().z + (cv2.GetTransformedVertex().z - cv1.GetTransformedVertex().z) * d)));
  
  				t.SetUV(vector2((cv1.GetUV().u + (cv2.GetUV().u - cv1.GetUV().u) * d),
  								(cv1.GetUV().v + (cv2.GetUV().v - cv1.GetUV().v) * d)));
  
  				t.SetTransformedUV(vector2((cv1.GetTransformedUV().u + (cv2.GetTransformedUV().u - cv1.GetTransformedUV().u) * d),
  										   (cv1.GetTransformedUV().v + (cv2.GetTransformedUV().v - cv1.GetTransformedUV().v) * d)));
  
  				clippedvert[curv++] = t;
  				clippedvert[curv++] = cv2;
  			}
  			else if (inside && (dist2 < -0.001))
  			{
  				clipped = true;
  				inside = false;
  				Vertex t;
  				float d = dist1 / (dist1 - dist2);
  				t.SetVertex(vector3((cv1.GetVertex().x + cv2.GetVertex().x - cv1.GetVertex().x) * d,
  					(cv1.GetVertex().y + cv2.GetVertex().y - cv1.GetVertex().y) * d,
  					(cv1.GetVertex().z + cv2.GetVertex().z - cv1.GetVertex().z) * d));
  
  				t.SetTransformedVertex(vector3((cv1.GetTransformedVertex().x + (cv2.GetTransformedVertex().x - cv1.GetTransformedVertex().x) * d),
  					(cv1.GetTransformedVertex().y + (cv2.GetTransformedVertex().y - cv1.GetTransformedVertex().y) * d),
  					(cv1.GetTransformedVertex().z + (cv2.GetTransformedVertex().z - cv1.GetTransformedVertex().z) * d)));
  
  				t.SetUV(vector2((cv1.GetUV().u + (cv2.GetUV().u - cv1.GetUV().u) * d),
  					(cv1.GetUV().v + (cv2.GetUV().v - cv1.GetUV().v) * d)));
  
  				t.SetTransformedUV(vector2((cv1.GetTransformedUV().u + (cv2.GetTransformedUV().u - cv1.GetTransformedUV().u) * d),
  					(cv1.GetTransformedUV().v + (cv2.GetTransformedUV().v - cv1.GetTransformedUV().v) * d)));
  
  				clippedvert[curv++] = t;
  			}
  			clipped = true;
  			cv1 = cv2;
  			dist1 = dist2;
  		}
  
  		if(!clipped)
  		{
  			vector3 one = v3.GetTransformedVertex() - v2.GetTransformedVertex();
  			vector3 two = v2.GetTransformedVertex() - v1.GetTransformedVertex();
  
  			vector3 norm = CROSS(one, two);
  
  			if(norm.z > 0.0f)
  				Core::Get()->DrawTriangle(v1, v2, v3);
  
  			continue;
  		}
 
  		if(curv < 3)
  			continue;
 
 		int numtris = 2+(curv - 4);
  
  		for(int k = 1; k < numtris + 1; ++k)
  		{	
  			Core::Get()->DrawTriangle(clippedvert[0], clippedvert[(k)], clippedvert[(k + 1)]);			
  		}
	}
}

void Tmpl8::Mesh::Transform( matrix& a_Matrix )
{
	for(unsigned int i = 1; i < m_OriginalVert.size(); ++i)
		m_Vert[i] = a_Matrix.Transform(m_OriginalVert[i]);

	matrix m = a_Matrix;
	m.SetTranslation(Tmpl8::vector3());

	for(unsigned int i = 1; i < m_OriginalNormal.size(); ++i)
		m_Normal[i] = m.Transform(m_OriginalNormal[i]).Normalized();
}

bool Tmpl8::Mesh::LoadOBJ( std::string a_FileName )
{
	// open the file for reading (folder string added to point to the data folder where assets are stored)
	std::string folder = "Data/";
	FILE* file = 0;

	fopen_s(&file, (folder + a_FileName).c_str(), "r");
	
	if(!file)
		return false;

	// Clear vector containers to store data (I know, vector containers shouldn't be used this low level, but they're easy and the speed increase is minimal in my case)
	m_Vert.clear();
	m_OriginalVert.clear();
	m_Normal.clear();
	m_OriginalNormal.clear();
	m_UV.clear();

	// store default values
 	m_Vert.push_back(vector3());
 	m_OriginalVert.push_back(vector3());
 	m_Normal.push_back(vector3());
 	m_OriginalNormal.push_back(vector3());
 	m_UV.push_back(vector2());

	char line[256];
	char val[256];
	Tmpl8::vector2 vec2;
	Tmpl8::vector3 vec3;
	int material = 0;

	// gogo read stuff
	while(fgets( line, 255, file ))
	{
		// found reference to a material file, load it
		if(!strncmp(line, "mtllib ", 7))
		{
			sprintf_s(val, 255, "%s", line + 7);
			val[strlen(val)-1] = '\0';
			SceneManager::Get()->GetScene()->GetMaterialManager()->LoadMaterials(val);
		}
		// material we need to use for the poly
		if(!strncmp(line, "usemtl ", 7))
		{
			sprintf_s(val, 255, "%s", line + 7);
			val[strlen(val)-1] = 0;
			material = SceneManager::Get()->GetScene()->GetMaterialManager()->GetMaterialID(val);
		}
		// got us some vertex data
		if(!strncmp(line, "v ", 2))
		{
			sscanf(line + 2, "%f %f %f", &vec3.x, &vec3.y, &vec3.z);
			m_OriginalVert.push_back(vec3);
			m_Vert.push_back(vec3);
		}
		// and some UVs
		if(!strncmp(line, "vt", 2))
		{
			sscanf(line + 2, "%f %f", &vec2.x, &vec2.y);
			m_UV.push_back(vec2);
		}
		// look at that! Normals!
		if( !strncmp( line, "vn", 2 ) )
		{
			sscanf(line + 2, "%f %f %f", &vec3.x, &vec3.y, &vec3.z);
			vec3.Normalize();
			m_OriginalNormal.push_back(vec3);
			m_Normal.push_back(vec3);
		}
		// face data, because.
		if( !strncmp( line, "f ", 2 ))
		{
			int vtn[9] = { 0,0,0, 0,0,0, 0,0,0 };
			bool weird = false;
			for( unsigned int i = 0; i < strlen( line ); i++ )
			{
				if( line[i] == '/' )
				{
					if( line[i+1] == '/' )
						weird = true;
				}
			}

			if( weird )
			{
				sscanf( line + 2, "%i//%i %i//%i %i//%i",
					&vtn[0], &vtn[2],
					&vtn[3], &vtn[5],
					&vtn[6], &vtn[8] );
			}
			else
			{
				sscanf( line + 2, "%i/%i/%i %i/%i/%i %i/%i/%i",
					&vtn[0], &vtn[1], &vtn[2],
					&vtn[3], &vtn[4], &vtn[5],
					&vtn[6], &vtn[7], &vtn[8] );
			}

			// got our stuff, add it.
			Poly t( vtn );
			t.SetMaterial(material);
			m_Face.push_back( t );
		}
	}
	fclose(file);

	SceneManager::Get()->GetScene()->SetPolyCount(SceneManager::Get()->GetScene()->GetPolyCount() + m_Face.size());

	return true;
}

void Tmpl8::Mesh::Scale( float a_Scale )
{
	// scale the model
	for(unsigned int i = 1; i < m_OriginalVert.size(); ++i)
		m_OriginalVert[i] *= a_Scale;
}