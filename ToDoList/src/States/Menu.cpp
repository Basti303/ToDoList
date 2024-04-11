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

	m_Sidebar.Init(m_WindowHeight);
	Content c;
	c.SetTitle("List1");
	c.AddTask("Task1");
	c.AddTask("Task2");
	Content f;
	f.SetTitle("List2");
	f.AddTask("Thing1");
	f.AddTask("Thing2");
	m_Contents.emplace_back(c);
	m_Contents.emplace_back(f);
	f.SetTitle("List3");
	m_Contents.emplace_back(f);
	f.SetTitle("List4");
	m_Contents.emplace_back(f);
	f.SetTitle("List5");
	m_Contents.emplace_back(f);

	if (m_Contents.size() > 0)
		m_SelectedContent = &m_Contents[0];
}

void Menu::ProcessInput(float deltaTime)
{
	Input::startOfFrame();

	// Check if an element was clicked and change selected element
	if (Input::isMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
	{
		
	}
}

void Menu::Update(float deltaTime)
{
	
	// input stuff
	Input::endOfFrame();
}

void Menu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.13f, 0.13f, 0.13f, 1.0f);

	std::vector<std::string> title;
	for (auto c : m_Contents)
		title.emplace_back(c.GetTitle());
	m_Sidebar.Draw(title, &m_Font, m_TextShader, m_RectangleShader, m_WindowHeight);
	m_Taskpanel.Draw(m_Contents[0].GetTasks(), &m_Font, m_TextShader, m_RectangleShader, 300.0f, m_WindowWidth, m_WindowHeight);
}
