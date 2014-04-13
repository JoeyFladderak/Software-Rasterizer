#ifndef _SPAN_H_
#define _SPAN_H_

namespace Tmpl8
{
	class Span
	{
	public:
		Span();
		~Span();

		const float GetVertX() const {return m_VertX;}
		const float GetVertY() const {return m_VertY;}
		const float GetVertZ() const {return m_VertZ;}

		const float GetNormalX() const {return m_NormalX;}
		const float GetNormalY() const {return m_NormalY;}
		const float GetNormalZ() const {return m_NormalZ;}

		const float GetU() const {return m_U;}
		const float GetV() const {return m_V;}

		void SetVertX(const float a_VertX) {m_VertX = a_VertX;}
		void SetVertY(const float a_VertY) {m_VertY = a_VertY;}
		void SetVertZ(const float a_VertZ) {m_VertZ = a_VertZ;}

		void SetNormalX(const float a_NormalX) {m_NormalX = a_NormalX;}
		void SetNormalY(const float a_NormalY) {m_NormalY = a_NormalY;}
		void SetNormalZ(const float a_NormalZ) {m_NormalZ = a_NormalZ;}

		void SetU(const float a_U) {m_U = a_U;}
		void SetV(const float a_V) {m_V = a_V;}

	private:

		float m_VertX;
		float m_VertY;
		float m_VertZ;

		float m_NormalX;
		float m_NormalY;
		float m_NormalZ;

		float m_U;
		float m_V;
	};
}

#endif