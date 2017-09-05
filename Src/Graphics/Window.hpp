#pragma once

#include "stdafx.hpp"

namespace Kaleid::Graphics
{
	class KALEID_GRAPHICS_API Window abstract
	{
	public:
		virtual void Dispose() = 0;

		virtual void MakeCurrent() = 0;
		virtual void SwapBuffers() = 0;

		virtual void GetSize(int* width, int* height) = 0;
		virtual void SetSize(const int width, const int height) = 0;

		virtual const char* GetTitle() = 0;
		virtual void SetTitle(const char* title) = 0;
	private:
	};
}