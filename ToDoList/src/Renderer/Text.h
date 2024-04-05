#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <map>

#include "Shader.h"

namespace Text
{
	struct Character
	{
		unsigned int TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		unsigned int Advance;
	};

	class Font
	{
	public:
		std::map<GLchar, Character> characters;

		Font();
		Font(const std::string& path);
		~Font();

		void loadFont(const std::string& path);
	};

	class Text2D
	{
	public:
		Text2D(std::string fontPath);
		~Text2D();

		void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);

	private:
		std::map<GLchar, Character> m_Characters;
		unsigned int m_VAO, m_VBO;
	};

	class TextComponent
	{
	public:
		TextComponent() = default;
		TextComponent(std::string fontPath);
		TextComponent(std::string fontPath, std::string text);
		TextComponent(Font* font);
		~TextComponent();

		void SetPosition(glm::vec2 position);
		void SetScale(float scale);
		void SetColor(glm::vec3 color);
		void SetText(std::string text);

		std::string GetText() const { return m_Text; }
		glm::vec2 GetPosition() const { return m_Position; }
		glm::vec3 GetColor() const { return m_Color; }
		float GetScale() const { return m_Scale; }

		float GetWidth() const { return m_Width; }
		float GetHeight() const { return m_Height; };

		void Draw(Shader& s);

	private:
		std::map<GLchar, Character> m_Characters;
		unsigned int m_VAO, m_VBO;
		Font* m_Font;

		glm::vec3 m_Color;
		glm::vec2 m_Position;
		float m_Scale;
		std::string m_Text;
		float m_Width, m_Height;

		void CalcWidthAndHeight();
	};
}