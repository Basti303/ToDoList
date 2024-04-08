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

	InputBox text = InputBox(m_Font, "Sample Text");
	text.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	text.SetPosition(glm::vec2(0.0f, 0.0f));
	m_InputBoxes.emplace_back(text);
	text.SetText("Another sample text");
	text.SetColor(glm::vec3(0.3f, 0.7f, 0.6f));
	text.SetPosition(glm::vec2(0.0f, m_WindowHeight - text.GetSize().y));
	m_InputBoxes.emplace_back(text);

	glm::vec2 rectSize(200.0f, m_WindowHeight);
	Rectangle rect = Rectangle(glm::vec2(rectSize.x / 2, rectSize.y / 2), glm::vec2(rectSize.x, rectSize.y - 2.f));
	rect.SetColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	rect.SetLineWidth(5);
	m_Rectangles.emplace_back(rect);
	
	Line line = Line(&m_WindowWidth, &m_WindowHeight, glm::vec2(0, 0), glm::vec2(m_WindowWidth, m_WindowHeight));
	line.SetColor(glm::vec4(0.0f, 1.0f, 0.3f, 1.0f));
	line.SetLineWidth(2.0f);
	m_Lines.emplace_back(line);

}

void Menu::ProcessInput(float deltaTime)
{
	Input::startOfFrame();

	// Check if an element was clicked and change selected element
	if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
	{
		for (auto& input : m_InputBoxes)
		{
			auto bounds = input.GetBounds();
			auto reversedCursorHeight = std::abs(Input::mouseY - m_WindowHeight);
			if (Input::mouseX < bounds.x + bounds.z && Input::mouseX > bounds.x &&
				reversedCursorHeight < bounds.y + bounds.w && reversedCursorHeight > bounds.y)
			{
				m_SelectedInputBox = &input;
				std::cout << "Clicked input with text: " << m_SelectedInputBox->GetText() << std::endl;
			}
		}
	}
}

void Menu::Update(float deltaTime)
{
	if (m_SelectedInputBox != nullptr)
		m_SelectedInputBox->Update();

	// input stuff
	Input::endOfFrame();
}

void Menu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.13f, 0.13f, 0.13f, 1.0f);

	for (auto& input : m_InputBoxes)
		input.Draw(m_TextShader);
	for (auto& rects : m_Rectangles)
		rects.Draw(m_RectangleShader);
	for (auto& lines : m_Lines)
		lines.Draw(m_RectangleShader);
}
