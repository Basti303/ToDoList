#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>

#include "Renderer/Shader.h"

class Rectangle
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

		unsigned indicesNotFilled[8]
		{
			0, 1,
			1, 2,
			2, 3,
			3, 0
		};
		
		unsigned indicesFilled[6]
		{
			0, 1, 3,
			1, 2, 3
		};
	};
public:
	Rectangle();
	Rectangle(glm::vec2 pos, glm::vec2 size);

	void SetPosition(glm::vec2 position) { m_Position = position; }
	void SetSize(glm::vec2 size);
	void SetColor(glm::vec4 color) { m_Color = color; }
	void SetFill(bool isFilled) { m_Fill = isFilled; }
	void SetLineWidth(float lineWidth) { m_LineWidth = lineWidth; }
	glm::vec2 GetSize() const { return m_Size; }
	glm::vec2 GetPosition() const { return m_Position; }
	glm::vec4 GetBounds() const { return glm::vec4(m_Position, m_Size); }
	bool GetIsFilled() const { return m_Fill; }
	float GetLineWidth() const { return m_LineWidth; }
	void Update();
	void Draw(Shader& shader);


private:
	glm::vec2 m_Position, m_Size;
	glm::vec4 m_Color;
	bool m_Fill = false;
	float m_LineWidth = 1;

	unsigned m_VB;
	unsigned m_VA;
	unsigned m_IBFill;
	unsigned m_IBNoFill;

	Vertices m_Vertices;

	void InitVertexBuffer();
	void InitVertexArray();
	void InitIndexBuffer();
};
