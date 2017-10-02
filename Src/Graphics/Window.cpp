#include "stdafx.hpp"
#include "Window.hpp"

using namespace Kaleid::Graphics;

Window::Window(int width, int height, const char* title)
{
	this->_handle = glfwCreateWindow(width, height, title, NULL, NULL);
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

void Window::SetVSyncMode(VSyncMode mode)
{
	this->MakeCurrent();
	glfwSwapInterval((this->_vsync_mode = mode));
}

VSyncMode Window::GetVSyncMode()
{
	return this->_vsync_mode;
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