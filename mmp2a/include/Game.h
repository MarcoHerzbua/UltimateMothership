// Game.h : Defines the class structure for the Game class

#pragma region include 

#pragma once
#include "stdafx.h"

#include "GameStateManager.h"
#include "InputManager.h"
#include "GameObjectManager.h"
#include "RenderManager.h"
#include "Eventbus.h"

#pragma endregion

using namespace std;
using namespace sf;

class Game
{
public:
	Game();

	void run();
	void setWindowSize(const Vector2u& size);

	RenderWindow* getWindowPtr();
	
private:
	RenderWindow m_window;

	GameStateManager * m_gameStateManager;
	InputManager * m_inputManager;
	GameObjectManager * m_gameObjectManager;
	RenderManager* m_renderManager;
	Eventbus * m_eventbus;

	Vector2u m_windowSize;

	bool init();

	void update(const float delta);
	void draw();

	void shutdown();

	void bindKeys();
};