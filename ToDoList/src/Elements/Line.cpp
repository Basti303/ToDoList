#include "Line.h"

#include <glm/gtc/matrix_transform.hpp>

Line::Line()
{
	InitVertexArray();
	InitVertexBuffer();
	InitIndexBuffer();
}

Line::Line(glm::vec2 start, glm::vec2 end)
	: m_Start(start), m_End(end)
{
	InitVertexArray();
	InitVertexBuffer();
	InitIndexBuffer();
	Update();
}

void Line::Update()
{
	m_Vertices.position[0] = m_Start.x;
	m_Vertices.position[1] = m_Start.y;
	m_Vertices.position[2] = m_End.x;
	m_Vertices.position[3] = m_End.y;
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices.position), m_Vertices.position, GL_STATIC_DRAW);
}

void Line::Draw(Shader& shader)
{
	shader.Bind();
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.SetUniformMat4f("model", model);
	shader.SetUniformVec4("color", m_Color);
	glBindVertexArray(m_VA);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
	glLineWidth(m_LineWidth);
	glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, nullptr);
	glLineWidth(1);
}

void Line::InitVertexBuffer()
{
	glGenBuffers(1, &m_VB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices.position), m_Vertices.position, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
}

void Line::InitVertexArray()
{
	glCreateVertexArrays(1, &m_VA);
	glBindVertexArray(m_VA);
}

void Line::InitIndexBuffer()
{
	glGenBuffers(1, &m_IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Vertices.indices), m_Vertices.indices, GL_STATIC_DRAW);
}
