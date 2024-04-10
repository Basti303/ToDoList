#pragma once

#include "glad/glad.h"

#include "StateSystem/StateManager.h"
#include "Core/Window.h"
#include "Renderer/Text.h"
#include "Renderer/Shader.h"
#include "Elements/InputBox.h"
#include "Elements/Rectangle.h"
#include "Elements/Line.h"
#include "Elements/Sidebar.h"
#include "Elements/Content.h"

class Menu : public StateSystem::State
{
public:
	Menu(Window* window, StateSystem::StateManager* states);
	~Menu();

	void Init() override;
	void ProcessInput(float deltaTime) override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	Window* m_Window;
	StateSystem::StateManager* m_States;
	int m_WindowWidth, m_WindowHeight;

	Shader m_TextShader, m_RectangleShader;
	Text::Font m_Font = Text::Font("res/fonts/BitterPro/BitterPro-Regular.ttf");

	Sidebar m_Sidebar;
	std::vector<Content> m_Contents;

	Content* m_SelectedContent = nullptr;
};