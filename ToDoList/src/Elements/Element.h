#pragma once

#include <glm/glm.hpp>
#include "Renderer/Shader.h"

namespace Elements
{
	class Element
	{
	public:
		virtual void SetPosition(glm::vec2 position) = 0;
		virtual glm::vec2 GetSize() const = 0;
		virtual glm::vec2 GetPosition() const = 0;
		virtual glm::vec4 GetBounds() const = 0;
		virtual void Update() = 0;
		virtual void Draw(Shader& shader) {};
		bool isSelected = false;
	};
}