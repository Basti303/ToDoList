#include "Window.h"
#include "Events/Input.h"

#include <iostream>

Window::Window()
{

}

Window::~Window()
{

}

Window* Window::CreateWindow(int width, int height, const char* title, bool fullscreenMode)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window* temp = new Window();
	if (fullscreenMode)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		temp->window = glfwCreateWindow(mode->width, mode->height, title, glfwGetPrimaryMonitor(), nullptr);
	}
	else
		temp->window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!temp->window)
	{
		printf("Failed to create window!\n");
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(temp->window);
	glfwSwapInterval(0.1f);

	return temp;
}

void Window::setMainCallbacks()
{
	if (window != nullptr)
	{
		glfwSetKeyCallback(window, Input::keyCallback);
		glfwSetCursorPosCallback(window, Input::mouseCallback);
		glfwSetMouseButtonCallback(window, Input::mouseButtonCallback);
		glfwSetScrollCallback(window, Input::mouseScrollCallback);
		glfwSetFramebufferSizeCallback(window, Input::framebufferSizeCallback);
	}
}

void Window::setCursorVisibility(bool visible)
{
	if (visible)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::close()
{
	if (window != nullptr)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::freeWindow(Window* window)
{
	if (window)
	{
		glfwDestroyWindow(window->window);
		delete window;
	}
}