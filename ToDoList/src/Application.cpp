#include "Application.h"

#include <iostream>
#include <memory>

#include "States/Menu.h"

Application::Application()
	: m_LastFrameTime(0), m_FPScap(165)
{
	if (!glfwInit())
	{
		std::cout << "Could not initialize GLFW!\n";
		return;
	}

	InitWindow();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Could not load glad!\n";
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// add first state
	m_States.Add(std::make_unique<Menu>(m_Window, &m_States), false);
}

Application::~Application()
{

}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_Window->window))
	{
		float currentTime = glfwGetTime();
		if (currentTime - m_LastFrameTime >= 1.0f / m_FPScap)
		{
			float deltaTime = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;
			//std::cout << "FPS: " << 1/deltaTime << "\n";

			m_States.ProcessStateAndChange();
			m_States.GetCurrent()->ProcessInput(deltaTime);
			m_States.GetCurrent()->Update(deltaTime);
			m_States.GetCurrent()->Render();

			glfwSwapBuffers(m_Window->window);
			glfwPollEvents();
		}
	}
}

void Application::InitWindow()
{
	m_Window = Window::CreateWindow(1360, 765, "ToDoList", false);
	m_Window->setMainCallbacks();
	m_Window->setCursorVisibility(true);
}