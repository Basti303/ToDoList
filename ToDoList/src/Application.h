#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Window.h"
#include "StateSystem/StateManager.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	Window* m_Window;
	StateSystem::StateManager m_States;

	float m_LastFrameTime;
	float m_FPScap;

	void InitWindow();
};