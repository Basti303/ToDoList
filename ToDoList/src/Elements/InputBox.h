#pragma once

#include <glad/glad.h>

#include "Renderer/Text.h"

class InputBox
{
public:
	InputBox(Text::Font& font);
	InputBox(Text::Font& font, std::string text);
	~InputBox() = default;

	void SetColor(glm::vec3 color) { m_TextComponent.SetColor(color); }
	void SetPosition(glm::vec2 position) { m_TextComponent.SetPosition(position); }
	void SetScale(float scale) { m_TextComponent.SetScale(scale); }
	void SetText(std::string text) { m_TextComponent.SetText(text); }

	std::string GetText() const { return m_TextComponent.GetText(); }
	glm::vec2 GetSize() const { return glm::vec2(m_TextComponent.GetWidth(), m_TextComponent.GetHeight()); }
	glm::vec2 GetPosition() const { return m_TextComponent.GetPosition(); }
	glm::vec4 GetBounds() const { return glm::vec4(m_TextComponent.GetPosition(), glm::vec2(m_TextComponent.GetWidth(), m_TextComponent.GetHeight())); }

	void Update();
	void Draw(Shader& s);

private:
	Text::TextComponent m_TextComponent;
	uint64_t m_CursorIndex;

	void Init(Text::Font& font);
};