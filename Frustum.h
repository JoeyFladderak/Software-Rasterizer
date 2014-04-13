#ifndef _FRUSTUM_H
#define _FRUSTUM_H

#include "Plane.h"

namespace Tmpl8
{
	class Frustum
	{
	public:

		enum
		{
			PLANE_LEFT = 0,
			PLANE_RIGHT = 1,
			PLANE_TOP = 2,
			PLANE_BOTTOM = 3,
			PLANE_NEAR = 4,
			PLANE_FAR = 5
		};

		Frustum();
		~Frustum();

		const vector3& GetFrustumPlane(unsigned int a_Index) const {return m_Plane[a_Index]->GetNormal();}
		const float GetFrustumDistance(unsigned int a_Index) const {return m_Plane[a_Index]->GetDistance();}

		void UpdateFrustum(matrix& a_Mat, vector3& a_Campos);

	private:

		Plane* m_Plane[6];

		float m_HeightNear;
		float m_WidthNear;
		float m_HeightFar;
		float m_WidthFar;
	};
}
#endif