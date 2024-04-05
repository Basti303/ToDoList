#include "Rectangle.h"

#include <glm/gtc/matrix_transform.hpp>

Elements::Rectangle::Rectangle()
{
	InitVertexArray();
	InitVertexBuffer();
	InitIndexBuffer();
}

Elements::Rectangle::Rectangle(glm::vec2 pos, glm::vec2 size)
	: m_Position(pos), m_Size(size)
{
	InitVertexArray();
	InitVertexBuffer();
	InitIndexBuffer();
	Update();
}

void Elements::Rectangle::SetSize(glm::vec2 size)
{
	m_Size = size;
	Update();
}

void Elements::Rectangle::Update()
{
	m_Vertices.position[0] = -m_Size.x / 2;
	m_Vertices.position[1] = -m_Size.y / 2;
	m_Vertices.position[2] =  m_Size.x / 2;
	m_Vertices.position[3] = -m_Size.y / 2;
	m_Vertices.position[4] =  m_Size.x / 2;
	m_Vertices.position[5] =  m_Size.y / 2;
	m_Vertices.position[6] = -m_Size.x / 2;
	m_Vertices.position[7] =  m_Size.y / 2;
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices.position), m_Vertices.position, GL_STATIC_DRAW);
}

void Elements::Rectangle::Draw(Shader& shader)
{
	shader.Bind();
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 1.0f));
	shader.SetUniformMat4f("model", model);
	shader.SetUniformVec4("color", m_Color);
	glBindVertexArray(m_VA);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Elements::Rectangle::InitVertexArray()
{
	glCreateVertexArrays(1, &m_VA);
	glBindVertexArray(m_VA);
}

void Elements::Rectangle::InitVertexBuffer()
{
	glGenBuffers(1, &m_VB);
	glBindBuffer(GL_ARRAY_BUFFER, m_VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices.position), m_Vertices.position, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
}

void Elements::Rectangle::InitIndexBuffer()
{
	glGenBuffers(1, &m_IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Vertices.indices), m_Vertices.indices, GL_STATIC_DRAW);
}
