#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Game/SceneBase.hpp"
#include "Jagerts.Kaleid.Game/Model.hpp"
#include "Jagerts.Kaleid.Graphics/Cube.hpp"
#include "Jagerts.Kaleid.Math/PerspectiveCamera.hpp"
#include <time.h>

namespace Jagerts::Genzh
{
	class TestScene : public Jagerts::Kaleid::Game::SceneBase
	{
	public:
		TestScene(Jagerts::Kaleid::Game::App* app);
		jkgSceneBaseHeader;
	private:
		void BuildShaderProgram();
		void BuildMesh();
		void CreateKeyboardBindings();

		Jagerts::Kaleid::Math::PerspectiveCamera _camera;
		Jagerts::Kaleid::Graphics::Cube _cube;
	};
}