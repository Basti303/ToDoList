#pragma once

#include <glad/glad.h>

#include "Renderer/Text.h"
#include "Element.h"

namespace Elements
{
	class InputBox : public Elements::Element
	{
	public:
		bool isSelected;

		InputBox(Text::Font& font);
		InputBox(Text::Font& font, std::string text);
		~InputBox() = default;

		void SetColor(glm::vec3 color) { m_TextComponent.SetColor(color); }
		void SetPosition(glm::vec2 position) { m_TextComponent.SetPosition(position); }
		void SetScale(float scale) { m_TextComponent.SetScale(scale); }
		void SetText(std::string text) { m_TextComponent.SetText(text); }

		glm::vec2 GetSize() const override { return glm::vec2(m_TextComponent.GetWidth(), m_TextComponent.GetHeight()); }
		glm::vec2 GetPosition() const override { return m_TextComponent.GetPosition(); }
		glm::vec4 GetBounds() const override { return glm::vec4(m_TextComponent.GetPosition(), glm::vec2(m_TextComponent.GetWidth(), m_TextComponent.GetHeight())); }

		void Update() override;
		void Draw(Shader& s) override;

	private:
		Text::TextComponent m_TextComponent;
		uint64_t m_CursorIndex;

		void Init(Text::Font& font);
	};
}