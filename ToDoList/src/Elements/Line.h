#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "Renderer/Shader.h"

class Line
{
public:
	struct Vertices
	{
		float position[4]
		{
			-0.5f, -0.5f,
			 0.5f,  0.5f
		};

		unsigned indices[2]
		{
			0, 1
		};
	};

public:
	Line();
	Line(glm::vec2 start, glm::vec2 end);

	void Update();
	void Draw(Shader& shader);

	void SetColor(glm::vec4 color) { m_Color = color; }
	void SetPosition(glm::vec2 start, glm::vec2 end) { m_Start = start, m_End = end; }
	void SetLineWidth(float lineWidth) { m_LineWidth = lineWidth; }

	glm::vec4 GetColor() const { return m_Color; }
	glm::vec2 GetStart() const { return m_Start; }
	glm::vec2 GetEnd() const { return m_End; }
	float GetLineWidth() const { return m_LineWidth; }

private:
	glm::vec2 m_Start, m_End;
	glm::vec4 m_Color = glm::vec4(1.0f);
	float m_LineWidth = 1;

	unsigned m_VB;
	unsigned m_VA;
	unsigned m_IB;

	Vertices m_Vertices;

	void InitVertexBuffer();
	void InitVertexArray();
	void InitIndexBuffer();
};