#pragma once

#include <vector>

#include "glm/glm.hpp"
#include "Renderer/Shader.h"
#include "Line.h"
#include "Renderer/Text.h"

class Sidebar
{
public:
	Sidebar();

	void Init(const int& windowHeight);
	void Update();
	void Draw(const std::vector<std::string>& title, short selectedIndex, Text::Font* font, Shader& textShader, Shader& lineShader, const int& windowHeight);

	float GetWidth() const { return m_Width; }
	float GetTopicHeight() const { return m_TopicBoundsHeight; }

private:
	float m_Width;
	float m_TopicBoundsHeight;

	Line m_RightLine;
};