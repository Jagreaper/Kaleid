#include "stdafx.hpp"
#include "Actor.hpp"
#include "VectorHelper.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Math;
using namespace Kaleid::Helpers;
using namespace Kaleid::Graphics;

void Actor::Render(Renderer*& renderer, std::function<void(ShaderProgram*&, Material* material)> arguments)
{
	for (std::pair<const char*, Model*> element : this->_models)
		element.second->Render(renderer, arguments);
}