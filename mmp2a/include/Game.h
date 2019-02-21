#pragma region include 

#pragma once
#include "stdafx.h"

class Eventbus;
class GameStateManager;
class InputManager;
class GameObjectManager;
class RenderManager;
class PlayerManager;

using namespace std;
using namespace sf;

#pragma endregion

class Game
{
public:
	Game();

	void run();
	void setWindowSize(const Vector2u& size);

	RenderWindow* getWindowPtr();
	
private:
	RenderWindow m_window;

	GameStateManager* m_gameStateManager;
	InputManager* m_inputManager;
	GameObjectManager* m_gameObjectManager;
	RenderManager* m_renderManager;
	PlayerManager* m_playerManager;

	Eventbus* m_eventbus;

	Vector2u m_windowSize;

	bool init();

	void update(float delta);
	void draw();

	void shutdown();

	void bindKeys();
};