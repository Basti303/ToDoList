#pragma once

#include <stack>
#include <memory>

#include "State.h"

namespace StateSystem
{
	class StateManager
	{
	public:
		StateManager();
		~StateManager();

		void Add(std::unique_ptr<State> toAdd, bool replace = false);
		void PopCurrent();
		void ProcessStateAndChange();
		std::unique_ptr<State>& GetCurrent();

	private:
		std::stack<std::unique_ptr<State>> stateStack;
		std::unique_ptr<State> new_State;

		bool replace;
		bool add;
		bool remove;	
	};
}