#pragma once

#include <string>
#include <vector>

class Content
{
public:
	Content();

	void AddTask(std::string task) { m_Tasks.emplace_back(task); }
	void SetTitle(std::string title) { m_Title = title; }

	std::string GetTitle() const { return m_Title; }
	std::vector<std::string> GetTasks() const { return m_Tasks; }

private:
	std::string m_Title;
	std::vector<std::string> m_Tasks;
};