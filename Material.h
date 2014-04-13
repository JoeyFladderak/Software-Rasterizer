#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <string>
#include "surface.h"

namespace Tmpl8
{
	class Material
	{
	public:

		Material();
		~Material();

		const std::string&	GetName()			const {return m_Name;}
		const int&			GetID()				const {return m_ID;}
		const Color&		GetAmbient()		{return m_Ka;}
		const Color&		GetDiffuse()		{return m_Kd;}
		const Color&		GetSpecular()		{return m_Ks;}
		const Color&		GetEmissive()		{return m_Em;}
		const int&			GetIllumination()	{return m_Illum;}
		const float&		GetShininess()		{return m_Ns;}
		const int&			GetDiffusemapID()	const {return m_MapKd_ID;}

		void	SetName(const std::string& a_Name)		{m_Name = a_Name;}
		void	SetID(const int& a_ID)					{m_ID = a_ID;}
		void	SetAmbient(const Color& a_Ka)			{m_Ka = a_Ka;}
		void	SetDiffuse(const Color& a_Kd)			{m_Kd = a_Kd;}
		void	SetSpecular(const Color& a_Ks)			{m_Ks = a_Ks;}
		void	SetEmissive(const Color& a_Em)			{m_Em = a_Em;}
		void	SetIllumination(const int& a_Illum)		{m_Illum = a_Illum;}
		void	SetShininess(const float& a_Ns)			{m_Ns = a_Ns;}
		void	SetDiffuseMap(const int& a_MapKd_ID)	{m_MapKd_ID = a_MapKd_ID;}

	private:

		std::string		m_Name;
		int				m_ID;
		Color			m_Ka;
		Color			m_Kd;
		Color			m_Ks;
		Color			m_Em;
		int				m_Illum;
		float			m_Ns;
		int				m_MapKd_ID;
	};
};

#endif