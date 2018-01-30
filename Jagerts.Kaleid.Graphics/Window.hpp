#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"

namespace Jagerts::Kaleid::Graphics
{
	class GraphicsFactory;

	enum CursorMode
	{
		Normal = 0x00034001,
		Hidden = 0x00034002,
		Disabled = 0x00034003,
	};

	enum VSyncMode
	{
		Off = 0,
		On = 1,
	};

	class JAGERTS_KALEID_GRAPHICS_API Window
	{
	public:
		void MakeCurrent();
		void SwapBuffers();

		void GetPosition(int* x, int* y) const;
		void SetPosition(const int x, const int y);

		void GetSize(unsigned int* width, unsigned int* height) const;
		void SetSize(const unsigned int width, const unsigned int height);

		void SetTitle(const char* title);
		void SetVSyncMode(VSyncMode mode);
		VSyncMode GetVSyncMode();

		void SetResizable(bool mode);
		void SetVisible(bool mode);
		void SetBorder(bool mode);
		void SetMaximized(bool mode);

		void ClampCursor();
		void CenterCursor();

		void SetCursorMode(CursorMode mode);
		CursorMode GetCursorMode();

		void Hide();
		void Restore();

		bool IsFocused() const;
		bool IsVisible() const;
		bool IsResizable() const;
		bool IsMaximised() const;
		bool HasBorder() const;
		bool Exists() const;
		static void PollEvents();

		char GetKeyState(int key_code) const;
		char GetMouseState(int mouse_code) const;
		void GetMousePosition(double* xpos, double* ypos) const;
	private:
		CursorMode _cursor_mode;
		VSyncMode _vsync_mode;
		Window(int width, int height, const char* title);
		void Dispose();

		friend class GraphicsFactory;
#ifdef JAGERTS_KALEID_GRAPHICS_DLL
		GLFWwindow* _handle;
#endif
	};
}