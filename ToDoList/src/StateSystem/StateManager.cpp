#include "StateManager.h"

StateSystem::StateManager::StateManager()
	: replace(false), add(false), remove(false)
{

}

StateSystem::StateManager::~StateManager()
{

}

void StateSystem::StateManager::Add(std::unique_ptr<State> toAdd, bool replace)
{
	add = true;
	new_State = std::move(toAdd);

	this->replace = replace;
}

void StateSystem::StateManager::PopCurrent()
{
	remove = true;
}

void StateSystem::StateManager::ProcessStateAndChange()
{
	if (remove && !stateStack.empty())
	{
		stateStack.pop();

		if (!stateStack.empty())
			//stateStack.top()->Start();

		remove = false;
	}

	if (add)
	{
		if (replace && !stateStack.empty())
		{
			stateStack.pop();
			replace = false;
		}

		if (!stateStack.empty())
			stateStack.top()->Pause();

		stateStack.push(std::move(new_State));
		stateStack.top()->Init();


		add = false;
	}
}

std::unique_ptr<StateSystem::State>& StateSystem::StateManager::GetCurrent()
{
	return stateStack.top();
}