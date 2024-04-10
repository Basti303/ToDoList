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
	void Draw(const std::vector<std::string>& title, Text::Font* font, Shader& textShader, Shader& lineShader, const int& windowHeight);

private:
	float m_Width;

	Line m_RightLine;
};