#ifndef _CAMERA_H
#define _CAMERA_H

#include "template.h"
#include "Frustum.h"

namespace Tmpl8
{
	class Camera
	{
	public:
		Camera(bool a_LookAt);
		~Camera();
		void Init(bool a_LookAt);

		void Update( float a_DT );
		void Lookat(const vector3& a_Target);

		const float& GetPan() const {return m_Pan;}
		const float& GetTilt() const {return m_Tilt;}
		const float& GetRoll() const {return m_Roll;}
		const vector3& GetUp() const {return m_Up;}
		const vector3& GetSide() const {return m_Side;}
		const vector3& GetForward() const {return m_Forward;}
		const vector3& GetPosition() const {return m_Pos;}
		matrix& GetMatrix() {return m_Mat;}
		matrix& GetMatrixInv() {return m_MatInv;}
		const float& GetZNear() const {return m_ZNear;}

		void SetPosition( const vector3& a_Pos ) {m_Pos = a_Pos;}
		void SetPan( const float& a_Pan ) {m_Pan = a_Pan;}
		void SetTilt( const float& a_Tilt ) {m_Tilt = a_Tilt;}
		void SetRoll( const float& a_Roll ) {m_Roll = a_Roll;}
		void SetMatrix(matrix a_Mat) {m_Mat = a_Mat;}

	private:

		void UpdateMatrix();

		matrix m_Mat;
		matrix m_MatInv;
		vector3 m_Pos;
		vector3 m_OriginalPos;
		vector3 m_Up;
		vector3 m_Side;
		vector3 m_Forward;
		float m_Pan;
		float m_Tilt;
		float m_Roll;
		float m_ZNear;
		float m_ZFar;
		bool m_LookAt;
	};
}

#endif 