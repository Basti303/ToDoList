#pragma once
#include <glad/glad.h>

#include "Element.h"

#include <glm/glm.hpp>

#include "Renderer/Shader.h"

namespace Elements
{
	class Rectangle : public Elements::Element
	{
	public:
		struct Vertices
		{
			float position[8]
			{
				-0.5f, -0.5f,
				 0.5f, -0.5f,
				 0.5f,  0.5f,
				-0.5f,  0.5f
			};

			unsigned indices[6]
			{
				0, 1, 3,
				1, 2, 3
			};
		};
	public:
		bool isSelected = false;

		Rectangle();
		Rectangle(glm::vec2 pos, glm::vec2 size);

		void SetPosition(glm::vec2 position) override { m_Position = position; }
		void SetSize(glm::vec2 size);
		void SetColor(glm::vec4 color) { m_Color = color; }
		glm::vec2 GetSize() const { return m_Size; }
		glm::vec2 GetPosition() const { return m_Position; }
		glm::vec4 GetBounds() const { return glm::vec4(m_Position, m_Size); }
		void Update();
		void Draw(Shader& shader);


	private:
		glm::vec2 m_Position, m_Size;
		glm::vec4 m_Color;

		unsigned m_VB;
		unsigned m_VA;
		unsigned m_IB;

		Vertices m_Vertices;

		void InitVertexBuffer();
		void InitVertexArray();
		void InitIndexBuffer();
	};
}