#ifndef _PLANE_H
#define _PLANE_H

#include "template.h"

namespace Tmpl8
{
	class Plane
	{
	public:

		Plane();
		~Plane();

		const vector3& GetNormal() const {return m_Normal;}
		const float GetDistance() const {return m_Distance;}

		void SetNormal(const vector3& a_Normal) {m_Normal = a_Normal;}
		void SetDistance(const float a_Distance) {m_Distance = a_Distance;}

	private:

		vector3 m_Normal;
		float m_Distance;
	};
}
#endif