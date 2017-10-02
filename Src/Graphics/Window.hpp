#pragma once

#include "stdafx.hpp"

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;

	enum VSyncMode
	{
		Off = 0,
		On = 1,
	};

	class KALEID_GRAPHICS_API Window sealed
	{
	public:
		void MakeCurrent();
		void SwapBuffers();

		void GetSize(unsigned int* width, unsigned int* height) const;
		void SetSize(const unsigned int width, const unsigned int height);

		void SetTitle(const char* title);
		void SetVSyncMode(VSyncMode mode);
		VSyncMode GetVSyncMode();

		bool IsFocused() const;
		bool IsVisible() const;
		bool IsResizable() const;
		bool HasBorder() const;
		bool Exists() const;
		static void PollEvents();

		char GetKeyState(int key_code) const;

	private:
		VSyncMode _vsync_mode;
		Window(int width, int height, const char* title);
		void Dispose();

		friend class GraphicsFactory;
#ifdef KALEID_GRAPHICS_DLL
		GLFWwindow* _handle;
#endif
	};
}
API_END