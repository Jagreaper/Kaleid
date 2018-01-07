#pragma once

#include "Jagerts.Kaleid.Shared\Common.hpp"
#include "Jagerts.Kaleid.Input\Keyboard.hpp"
#include "Jagerts.Kaleid.Input\Mouse.hpp"
#include <ctime>


#define jkgUsingSceneBase \
using Jagerts::Kaleid::Game::SceneBase::Load; \
using Jagerts::Kaleid::Game::SceneBase::Update; \
using Jagerts::Kaleid::Game::SceneBase::Poll

#define jkgImplementAbstractSceneBase \
void Dispose(); \
void Render() \

#define jkgImplementSceneBase \
jkgImplementAbstractSceneBase; \
void Load(); \
void Update(); \

#define jkgImplementAbstractSceneBaseVirtual \
virtual void Dispose(); \
virtual void Render() \

#define jkgImplementSceneBaseVirtual \
jkgImplementAbstractSceneBaseVirtual; \
virtual void Load(); \
virtual void Update(); \

namespace Jagerts::Kaleid::Graphics
{
	class Renderer;
	class GraphicsFactory;
}

namespace Jagerts::Kaleid::Game
{
	class App;

	class JAGERTS_KALEID_GAME_API SceneBase abstract
	{
	public:
		SceneBase(App*& app);
		virtual void Render() = 0;
		virtual void Dispose() = 0;
		virtual void Poll(Jagerts::Kaleid::Graphics::Window*& window);
		virtual void Load();
		virtual void Update();
		const double& GetDeltaTime() const;
	protected:
		App* _app;
		Jagerts::Kaleid::Graphics::Renderer* _renderer;
		Jagerts::Kaleid::Graphics::GraphicsFactory* _graphics_factory;
		Jagerts::Kaleid::Input::Keyboard _keyboard;
		Jagerts::Kaleid::Input::Mouse _mouse;

		clock_t _o_time;
		clock_t _n_time;
		double _delta_time;
	};
}