#include "Material.h"

Tmpl8::Material::Material()
{
	m_Name		= "";
	m_ID		= 0;
	m_Ka		= Color();
	m_Kd		= Color();
	m_Ks		= Color();
	m_Em		= Color();
	m_Illum		= 0;
	m_Ns		= 0;
	m_MapKd_ID	= 0;
}

Tmpl8::Material::~Material()
{

}