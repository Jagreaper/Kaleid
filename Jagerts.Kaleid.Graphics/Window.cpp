#include "Window.hpp"

using namespace Jagerts::Kaleid::Graphics;

Window::Window(int width, int height, const char* title)
{
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	this->_handle = glfwCreateWindow(width, height, title, NULL, NULL);
	this->_cursor_mode = CursorMode::Normal;
	this->SetVSyncMode(VSyncMode::Off);
}

void Window::Dispose()
{
	if (this->_handle != NULL)
	{
		glfwDestroyWindow(this->_handle);
		this->_handle = NULL;
	}
}

void Window::MakeCurrent()
{
	glfwMakeContextCurrent(this->_handle);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(this->_handle);
}

void Window::GetPosition(int* x, int* y) const
{
	glfwGetWindowPos(this->_handle, x, y);
}

void Window::SetPosition(const int x, const int y)
{
	glfwSetWindowPos(this->_handle, (int)x, (int)y);
}

void Window::GetSize(unsigned int* width, unsigned int* height) const
{
	int i_width, i_height;
	glfwGetWindowSize(this->_handle, &i_width, &i_height);
	*width = (int)i_width;
	*height = (int)i_height;
}

void Window::SetSize(const unsigned int width, const unsigned int height)
{
	glfwSetWindowSize(this->_handle, (int)width, (int)height);
}

void Window::SetTitle(const char* title)
{
	glfwSetWindowTitle(this->_handle, title);
}

void Window::ClampCursor()
{
	unsigned int width, height;
	this->GetSize(&width, &height);

	double mouse_x, mouse_y;
	this->GetMousePosition(&mouse_x, &mouse_y);

	if (mouse_x < 0)
		glfwSetCursorPos(this->_handle, 0, mouse_y);
	if (mouse_x > width)
		glfwSetCursorPos(this->_handle, width, mouse_y);
	if (mouse_y < 0)
		glfwSetCursorPos(this->_handle, mouse_x, 0);
	if (mouse_y > height)
		glfwSetCursorPos(this->_handle, mouse_x, height);
}

void Window::CenterCursor()
{
	unsigned int width, height;
	this->GetSize(&width, &height);
	glfwSetCursorPos(this->_handle, width / 2, height / 2);
}

void Window::SetCursorMode(CursorMode mode)
{
	glfwSetInputMode(this->_handle, GLFW_CURSOR, (this->_cursor_mode = mode));
}

CursorMode Window::GetCursorMode()
{
	return this->_cursor_mode;
}

void Window::Hide()
{
	glfwHideWindow(this->_handle);
}

void Window::Restore()
{
	glfwRestoreWindow(this->_handle);
}

void Window::SetVSyncMode(VSyncMode mode)
{
	this->MakeCurrent();
	glfwSwapInterval((this->_vsync_mode = mode));
}

VSyncMode Window::GetVSyncMode()
{
	return this->_vsync_mode;
}

void Window::SetResizable(bool mode)
{
	this->MakeCurrent();
	glfwWindowHint(GLFW_RESIZABLE, mode);
}

void Window::SetVisible(bool mode)
{
	this->MakeCurrent();
	glfwWindowHint(GLFW_VISIBLE, mode);
}

void Window::SetBorder(bool mode)
{
	this->MakeCurrent();
	glfwWindowHint(GLFW_DECORATED, mode);
}

void Window::SetMaximized(bool mode)
{
	this->MakeCurrent();
	glfwWindowHint(GLFW_MAXIMIZED, mode);
}

bool Window::IsFocused() const
{
	return glfwGetWindowAttrib(this->_handle, GLFW_FOCUSED);
}

bool Window::IsVisible() const
{
	return glfwGetWindowAttrib(this->_handle, GLFW_VISIBLE);
}

bool Window::IsResizable() const
{
	return glfwGetWindowAttrib(this->_handle, GLFW_RESIZABLE);
}

bool Window::IsMaximised() const
{
	return glfwGetWindowAttrib(this->_handle, GLFW_MAXIMIZED);
}

bool Window::HasBorder() const
{
	return glfwGetWindowAttrib(this->_handle, GLFW_DECORATED);
}

bool Window::Exists() const
{
	return !glfwWindowShouldClose(this->_handle);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

char Window::GetKeyState(int key_code) const
{
	return glfwGetKey(this->_handle, key_code);
}

char Window::GetMouseState(int mouse_code) const
{
	return glfwGetMouseButton(this->_handle, mouse_code);
}

void Window::GetMousePosition(double* xpos, double* ypos) const
{
	glfwGetCursorPos(this->_handle, xpos, ypos);
}