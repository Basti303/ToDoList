#include <glad/glad.h>

#include "Input.h"

#include <iostream>

namespace Input
{
	bool keyPressedData[GLFW_KEY_LAST] = {};
	bool lastFramekeyPressedData[GLFW_KEY_LAST] = {};
	std::vector<int> releasedKeys;
	bool mouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST] = {};
	bool lastFrameMouseButtonReleasedData[GLFW_MOUSE_BUTTON_LAST];
	std::vector<int> releasedMouseButtons;
	float mouseX = 0.0f;
	float mouseY = 0.0f;
	bool firstMouse = true;
	float mouseScrollX = 0.0f;
	float mouseScrollY = 0.0f;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key >= 0 && key < GLFW_KEY_LAST)
		{
			if(mods == GLFW_MOD_SHIFT || key < 65 || key > 90 && key < 97 || key > 122)
				keyPressedData[key] = action == GLFW_PRESS;
			else
				keyPressedData[key + 32] = action == GLFW_PRESS;
		}
	}

	void mouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			firstMouse = false;
		}
		mouseX = (float)xpos;
		mouseY = (float)ypos;
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
			mouseButtonPressedData[button] = action == GLFW_PRESS;
	}

	void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouseScrollX = (float)xoffset;
		mouseScrollY = (float)yoffset;
	}

	void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	//bool isKeyDown(int key)
	//{
	//	if (key >= 0 && key < GLFW_KEY_LAST)
	//		return keyPressedData[key];
	//	return false;
	//}

	bool isKeyDown(GLFWwindow* window, int key)
	{
		if (glfwGetKey(window, key) == GLFW_PRESS)
		{
			return true;
		}
		return false;
	}

	bool isKeyReleased(int key)
	{
		for (auto& s : releasedKeys)
		{
			if (s == key)
				return true;
		}
		return false;
	}

	bool isMouseButtonDown(int mouseButton)
	{
		if (mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST)
			return mouseButtonPressedData[mouseButton];
		return false;
	}

	bool isMouseButtonReleased(int button)
	{
		for (auto& s : releasedMouseButtons)
		{
			if (s == button)
				return true;
		}
		return false;
	}

	void startOfFrame()
	{
		// keys
		for (size_t i = 0; i < GLFW_KEY_LAST; i++)
		{
			if (lastFramekeyPressedData[i] && !keyPressedData[i])
			{
				releasedKeys.emplace_back(i);
			}
		}
		// mouse buttons
		for (size_t i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
		{
			if (lastFrameMouseButtonReleasedData[i] && !mouseButtonPressedData[i])
			{
				releasedMouseButtons.emplace_back(i);
			}
		}
	}

	void endOfFrame()
	{
		// keys
		for (size_t i = 0; i < GLFW_KEY_LAST; i++)
			lastFramekeyPressedData[i] = keyPressedData[i];
		releasedKeys.clear();
		// mouse
		for (size_t i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
			lastFrameMouseButtonReleasedData[i] = mouseButtonPressedData[i];
		releasedMouseButtons.clear();
	}
}