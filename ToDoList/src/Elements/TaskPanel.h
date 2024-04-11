#pragma once

#include <vector>
#include <string>

#include "Renderer/Text.h"
#include "Renderer/Shader.h"

class TaskPanel
{
public:
	TaskPanel();

	void Update();
	void Draw(const std::vector<std::string>& tasks, Text::Font* font, Shader& textShader, Shader& lineShader, const int& sidebarWidth, const int& windowWidth, const int& windowHeight);

private:
};