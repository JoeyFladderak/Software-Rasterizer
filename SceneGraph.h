#ifndef _SCENEGRAPH_H_
#define _SCENEGRAPH_H_

#include "template.h"
#include <vector>

namespace Tmpl8
{
	class Mesh;
	class Node
	{
	public:
		
		Node();
		Node(Mesh* a_Mesh);
		~Node();

		void Render(matrix& a_Matrix = matrix());
		void UpdateWithCam(matrix& a_Matrix = matrix());
		void AddChild(Node* a_Child);
		Node* AddChild(std::string a_FileName, std::string a_Name);
		void RemoveChild(Node* a_Child);

		void Scale(float a_Scale);

		float& GetPan()  {return m_Pan;}
		float& GetTilt()  {return m_Tilt;}
		float& GetRoll()  {return m_Roll;}
		vector3& GetUp()  {return m_Up;}
		vector3& GetSide()  {return m_Side;}
		vector3& GetForward()  {return m_Forward;}
		vector3& GetPosition()  {return m_Pos;}
		matrix& GetMatrix()  {return m_Transform;}

		void SetPosition( const vector3& a_Pos ) {m_Pos = a_Pos;}
		void SetPan( const float& a_Pan ) {m_Pan = a_Pan;}
		void SetTilt( const float& a_Tilt ) {m_Tilt = a_Tilt;}
		void SetRoll( const float& a_Roll ) {m_Roll = a_Roll;}

	private:

		Mesh* m_Mesh;
		
		matrix m_Transform;
		vector3 m_Pos;
		vector3 m_Up;
		vector3 m_Side;
		vector3 m_Forward;
		float m_Pan;
		float m_Tilt;
		float m_Roll;

		Node* m_Parent;
		std::vector<Node*>	m_Child;

	};
}

#endif
