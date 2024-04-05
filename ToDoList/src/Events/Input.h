#pragma once

#include "GLFW/glfw3.h"
#include <vector>

namespace Input
{
	extern bool keyPressedData[GLFW_KEY_LAST];
	extern bool lastFramekeyPressedData[GLFW_KEY_LAST];
	extern std::vector<int> releasedKeys;
	extern bool mouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST];
	extern bool lastFrameMouseButtonReleasedData[GLFW_MOUSE_BUTTON_LAST];
	extern std::vector<int> releasedMouseButtons;
	extern float mouseX;
	extern float mouseY;
	extern bool firstMouse;
	extern float mouseScrollX;
	extern float mouseScrollY;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	//bool isKeyDown(int key);
	bool isKeyDown(GLFWwindow* window, int key);
	bool isKeyReleased(int key);
	bool isMouseButtonDown(int mouseButton);
	bool isMouseButtonReleased(int button);
	void startOfFrame();
	void endOfFrame();
}