#ifndef _CORE_H_
#define _CORE_H_

#include "template.h"
#include "surface.h"
#include "Vertex.h"
#include "RenderTarget.h"

namespace Tmpl8
{
	class RenderTarget;
	class Core
	{
	public:
		
		virtual ~Core();	

		static Core* Create();
		static Core* Get() {return m_Core;}

		void Init();
		void DrawTriangle(const Vertex& a_V1, const Vertex& a_V2, const Vertex& a_V3);
		void SetTexture(Surface* a_Texture) { m_Texture = a_Texture;}
		void SetColor(Color a_Color) {m_Color = a_Color;}
		Pixel GetUVColor(float a_U, float a_V);
		Color GetColor() {return m_Color;}
		Surface* GetTexture() {return m_Texture;}

		void SetRenderTarget(RenderTarget* a_Target) {m_CurrentRenderTarget = a_Target;}
		RenderTarget* GetRenderTarger() {return m_CurrentRenderTarget;}

		Color SetShading(const vector3& a_WorldPos, const vector3& a_Normal, const vector2& a_UV, int a_ShadingType);

		void Clear();

	private:

		Core();

		RenderTarget* m_CurrentRenderTarget;

		Surface* m_Texture;
		Color m_Color;

		static Core*	m_Core;

	};
}

#endif
