#pragma once

#include "stdafx.hpp"
#include "SceneBase.hpp"

namespace Kaleid::Game
{
	class RootScene : public SceneBase
	{
	public:
		RootScene(App*& app);
		void Load();
		void Update();
		void Render();
		void Dispose();
	};
}