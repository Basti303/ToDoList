#include "Sidebar.h"

Sidebar::Sidebar()
	: m_Width(300)
{
	
}

void Sidebar::Init(const int& windowHeight)
{
	m_RightLine.SetColor(glm::vec4(0.2f, 0.2f, 0.8f, 1.0f));
	m_RightLine.SetLineWidth(4.0f);
	m_RightLine.SetPosition(glm::vec2(m_Width, 0), glm::vec2(m_Width, windowHeight));
	m_RightLine.Update();
}

void Sidebar::Update()
{
}

void Sidebar::Draw(const std::vector<std::string>& title, Text::Font* font, Shader& textShader, Shader& lineShader, const int& windowHeight)
{
	m_RightLine.Draw(lineShader);

	Text::TextComponent t(font);
	t.SetColor(glm::vec3(1.0f));
	Line l;
	l.SetColor(glm::vec4(0.2f, 0.2f, 0.8f, 1.0f));
	l.SetLineWidth(2.0f);
	for (int64_t i = 0; i < title.size(); i++)
	{
		t.SetText(title[i]);
		t.SetPosition(glm::vec2(m_Width / 2 - t.GetWidth() / 2, windowHeight - 100 * i - 50 - t.GetHeight() / 2));
		float lineHeight = windowHeight - 100 * (i + 1);
		l.SetPosition(glm::vec2(0.0f, lineHeight), glm::vec2(m_Width, lineHeight));
		l.Update();
		l.Draw(lineShader);
		t.Draw(textShader);
	}
}
