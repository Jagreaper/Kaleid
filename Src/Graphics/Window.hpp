#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;

	class KALEID_GRAPHICS_API Window sealed
	{
	public:
		void MakeCurrent();
		void SwapBuffers();

		void GetSize(unsigned int* width, unsigned int* height);
		void SetSize(const unsigned int width, const unsigned int height);

		void SetTitle(const char* title);
		bool Exists();
		static void PollEvents();

		char GetKeyState(int key_code);

	private:
		Window(int width, int height, const char* title);
		void Dispose();

		friend class GraphicsFactory;
#ifdef KALEID_GRAPHICS_DLL
		GLFWwindow* _handle;
#endif
	};
}
API_END