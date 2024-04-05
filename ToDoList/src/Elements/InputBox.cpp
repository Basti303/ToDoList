#include "InputBox.h"

#include "Events/Input.h"

Elements::InputBox::InputBox(Text::Font& font)
{
	Init(font);
	m_CursorIndex = 0;
}

Elements::InputBox::InputBox(Text::Font& font, std::string text)
{
	Init(font);
	m_TextComponent.SetText(text);
	m_CursorIndex = text.size();
}

void Elements::InputBox::Update()
{
	std::string newString = m_TextComponent.GetText();
	for (auto& key : Input::releasedKeys)
	{
		//std::cout << key << std::endl;
		if (key == GLFW_KEY_BACKSPACE)
		{
			if (newString.size() != 0)
			{
				m_CursorIndex--;
				newString.erase(m_CursorIndex);
			}
			continue;
		}
		else if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
			continue;
		std::string y;
		y = (char)key;
		newString.insert((size_t)m_CursorIndex, y);
		m_CursorIndex++;
	}
	m_TextComponent.SetText(newString);
}

void Elements::InputBox::Draw(Shader& shader)
{
	m_TextComponent.Draw(shader);
}

void Elements::InputBox::Init(Text::Font& font)
{
	isSelected = false;
	m_TextComponent = Text::TextComponent(&font);
	m_TextComponent.SetColor(glm::vec3(1.0f));
	m_TextComponent.SetPosition(glm::vec3(0.0f));
	m_TextComponent.SetScale(1.0f);
}