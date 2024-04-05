#pragma once

#include "GLFW/glfw3.h"

class Window
{
public:
	GLFWwindow* window;
	Window();
	~Window();

	static Window* CreateWindow(int width, int height, const char* title, bool fullscreenMode = false);
	static void freeWindow(Window* window);
	void close();
	void setMainCallbacks();
	void setCursorVisibility(bool visible);

private:
};