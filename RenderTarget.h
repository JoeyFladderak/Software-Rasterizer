#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

#include "template.h"
#include "surface.h"
#include "Vertex.h"
#include "Span.h"
#include "SceneManager.h"
#include "Core.h"

namespace Tmpl8
{
	class RenderTarget
	{
	public:
		
		RenderTarget(unsigned int a_Width, unsigned int a_Height);
		void DrawTriangle(const Vertex& a_V1, const Vertex& a_V2, const Vertex& a_V3);
		Surface* GetBuffer() {return m_Buffer;}
		unsigned int GetWidth() {return m_Width;}
		unsigned int GetHeight() {return m_Height;}
		void Clear();
		void SetShading(int a_Shading) {m_CurrentShading = a_Shading;}

		~RenderTarget();	

	private:

		void ScanEdge(const Vertex& a_V1, const Vertex& a_V2);
		void ResetSpanLine( int line );

		unsigned int m_Width;
		unsigned int m_Height;

		int m_CurrentShading;

		Surface* m_Buffer;
		Color m_Color;
		float* m_ZBuffer;
		Span* m_SpanMax;
		Span* m_SpanMin;

	};
}

#endif
