#include "Menu.h"

#include "Events/Input.h"

Menu::Menu(Window* window, StateSystem::StateManager* states)
	: m_Window(window), m_States(states)
{
}

Menu::~Menu()
{
	
}

void Menu::Init()
{
	m_TextShader.MakeShader("res/shader/Font.shader");
	glfwGetWindowSize(m_Window->window, &m_WindowWidth, &m_WindowHeight);
	glm::mat4 projection = glm::ortho(0.0f, (float)m_WindowWidth, 0.0f, (float)m_WindowHeight);
	m_TextShader.Bind();
	m_TextShader.SetUniformMat4f("projection", projection);

	m_RectangleShader.MakeShader("res/shader/Rectangle.shader");
	m_RectangleShader.Bind();
	m_RectangleShader.SetUniformMat4f("projection", projection);
	glm::mat4 view =glm::mat4(1.0f);
	m_RectangleShader.SetUniformMat4f("view", view);

	Elements::Rectangle* rect = new Elements::Rectangle(glm::vec2(30, 30), glm::vec2(10.0f, 600.0f));
	rect->SetColor(glm::vec4(0.0f, 0.8f, 0.9f, 1.0f));
	m_Elements.emplace_back(rect);

	m_Elements.emplace_back(new Elements::InputBox(m_Font, "Gay"));
	m_Elements[1]->SetPosition(glm::vec2(0.0f, (float)m_WindowHeight - m_Elements[1]->GetSize().y));
}

void Menu::ProcessInput(float deltaTime)
{
	Input::startOfFrame();

	// Check if an element was clicked and change selected element
	if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
	{
		for (auto& element : m_Elements)
		{
			auto bounds = element->GetBounds();
			auto reversedCursorHeight = std::abs(Input::mouseY - m_WindowHeight);
			if (Input::mouseX < bounds.x + bounds.z && Input::mouseX > bounds.x &&
				reversedCursorHeight < bounds.y + bounds.w && reversedCursorHeight > bounds.y)
			{
				if (m_SelectedElement != nullptr)
					m_SelectedElement->isSelected;
				element->isSelected = true;
				m_SelectedElement = element;
				std::cout << "Clicked element!\n";
			}
		}
	}
}

void Menu::Update(float deltaTime)
{
	if(m_SelectedElement != nullptr)
		m_SelectedElement->Update();

	// input stuff
	Input::endOfFrame();
}

void Menu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.13f, 0.13f, 0.13f, 1.0f);

	m_Elements[0]->Draw(m_RectangleShader);
	m_Elements[1]->Draw(m_TextShader);
}

void Menu::DeselectAllElements()
{
	for (auto& element : m_Elements)
		element->isSelected = false;
}
