#pragma once

namespace StateSystem
{
	class State
	{
	public:
		State() {};
		virtual ~State() {};

		virtual void Init() = 0;
		virtual void ProcessInput(float deltaTime) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		virtual void Pause() {};
		virtual void Start() {};
	};
}