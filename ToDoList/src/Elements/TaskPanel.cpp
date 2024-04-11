#include "TaskPanel.h"

#include "Line.h"

TaskPanel::TaskPanel()
{
}

void TaskPanel::Update()
{
}

void TaskPanel::Draw(const std::vector<std::string>& tasks, Text::Font* font, Shader& textShader, Shader& lineShader, const int& sidebarWidth, const int& windowWidth, const int& windowHeight)
{
	Text::TextComponent t(font);
	t.SetColor(glm::vec3(1.0f));
	t.SetScale(0.8f);
	Line l;
	l.SetColor(glm::vec4(1.0f, 0.2f, 1.0f, 1.0f));
	float lineThickness = 3.0f;
	l.SetLineWidth(lineThickness);
	for (int64_t i = 0; i < tasks.size(); i++)
	{
		t.SetText(tasks[i]);
		float topOffset = 50.0f;
		float lineOffset = 60.0f;
		float lineHeight = windowHeight - i * lineOffset - topOffset;
		float sidebarOffset = 40.0f;
		float lineWidth = 20.0f;
		float lineTextOffset = 10.0f;
		l.SetPosition(glm::vec2(sidebarWidth + sidebarOffset, lineHeight), glm::vec2(sidebarWidth + sidebarOffset + lineWidth, lineHeight));
		t.SetPosition(glm::vec2(sidebarWidth + sidebarOffset + lineWidth + lineTextOffset, l.GetEnd().y - t.GetHeight() / 2 + lineThickness / 2));
		l.Update();
		l.Draw(lineShader);
		t.Draw(textShader);
	}
}
