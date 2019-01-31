// Game.cpp : Defines the entry point for the console application.

#pragma region include

#include "stdafx.h"
#include "Game.h"

// game classes
#include "GameStateManager.h"

// interface 
#include "IGameState.h"

// derived
#include "MenuState.h"
#include "MainState.h"

// enum
#include "GameStates.h"

// singleton
#include "InputManager.h"

#pragma endregion

Game::Game()
{
	m_windowSize = Vector2u(800, 600);
}

void Game::run()
{
	if (!init())
		return;

	while (m_window.isOpen())
	{
		Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				m_window.close();
		}

		static Clock clock;
		Time deltaTime = clock.restart();
		const float deltaTimeSeconds = deltaTime.asSeconds();

		update(deltaTimeSeconds);
		draw();
	}

	shutdown();
}

void Game::setWindowSize(const Vector2u& size)
{
	m_windowSize = size;
	
	if (&m_window)
		m_window.setSize(m_windowSize);
}

RenderWindow* Game::getWindowPtr() 
{
	return &m_window;
}

bool Game::init()
{
	m_window.create(VideoMode(m_windowSize.x, m_windowSize.y), "SFML");
	// m_window.create(VideoMode(m_windowSize.x, m_windowSize.y), "SFML", Style::Fullscreen);

	m_gameStateManager = &GameStateManager::getInstance();
	m_inputManager = &InputManager::getInstance();
	m_gameObjectManager = &GameObjectManager::getInstance();
	m_renderManager = &RenderManager::getInstance();
	m_playerManager = &PlayerManager::getInstance();

	m_eventbus = &Eventbus::getInstance();

	m_gameStateManager->init(this);
	m_gameObjectManager->init(this);

	MenuState * menuState = new MenuState();
	MainState * mainState = new MainState();

	m_gameStateManager->setState(GameStates::MENU_STATE);

	bindKeys();

	return true;
}

void Game::update(const float deltaTimeSeconds)
{
	m_eventbus->update();
	m_gameStateManager->update(deltaTimeSeconds);
	//has to be called after GameStateMng->update; potential Bug
	m_inputManager->update();
}

void Game::draw()
{
	m_window.clear(Color(255,255,255));

	m_renderManager->draw(&m_window);

	m_window.display();
}

void Game::shutdown()
{
	m_gameStateManager->exit();
	GameplayStateManager::getInstance().exit();
}

void Game::bindKeys()
{
	m_inputManager->bind(ESCAPE_ACTION, Keyboard::Escape, 0);
	m_inputManager->bind(ESCAPE_ACTION, BUTTON_BACK, 0);
	m_inputManager->bind(ESCAPE_ACTION, Keyboard::Escape, 1);
	m_inputManager->bind(ESCAPE_ACTION, BUTTON_BACK, 1);


	m_inputManager->bind(A_BUTTON_ACTION, BUTTON_A, 0);
	m_inputManager->bind(X_BUTTON_ACTION, BUTTON_X, 0);
	m_inputManager->bind(B_BUTTON_ACTION, BUTTON_B, 0);
	m_inputManager->bind(Y_BUTTON_ACTION, BUTTON_Y, 0);
	m_inputManager->bind(NEXT_UNIT_ACTION, BUTTON_RB, 0);
	m_inputManager->bind(PREV_UNIT_ACTION, BUTTON_LB, 0);

	m_inputManager->bind(MOVE_UP_ACTION, LEFT_STICK_UP, 0);
	m_inputManager->bind(MOVE_LEFT_ACTION, LEFT_STICK_LEFT, 0);
	m_inputManager->bind(MOVE_DOWN_ACTION, LEFT_STICK_DOWN, 0);
	m_inputManager->bind(MOVE_RIGHT_ACTION, LEFT_STICK_RIGHT, 0);

	m_inputManager->bind(A_BUTTON_ACTION, Keyboard::Down, 1);
	m_inputManager->bind(X_BUTTON_ACTION, Keyboard::Left, 1);
	m_inputManager->bind(B_BUTTON_ACTION, Keyboard::Right, 1);
	m_inputManager->bind(Y_BUTTON_ACTION, Keyboard::Up, 1);
	m_inputManager->bind(NEXT_UNIT_ACTION, Keyboard::E, 1);
	m_inputManager->bind(PREV_UNIT_ACTION, Keyboard::Q, 1);


	m_inputManager->bind(MOVE_UP_ACTION, Keyboard::W, 1);
	m_inputManager->bind(MOVE_LEFT_ACTION, Keyboard::A, 1);
	m_inputManager->bind(MOVE_DOWN_ACTION, Keyboard::S, 1);
	m_inputManager->bind(MOVE_RIGHT_ACTION, Keyboard::D, 1);


	//m_inputManager->bind(MOVE_UP_ACTION, Keyboard::W, 1);
	//m_inputManager->bind(MOVE_LEFT_ACTION, Keyboard::A, 1);
	//m_inputManager->bind(MOVE_DOWN_ACTION, Keyboard::S, 1);
	//m_inputManager->bind(MOVE_RIGHT_ACTION, Keyboard::D, 1);

	m_inputManager->bind(SWITCH_HUMAN_AI, Keyboard::Num1, 0);
	m_inputManager->bind(SWITCH_HUMAN_AI, Keyboard::Num1, 1);

	m_inputManager->bind(NEXT_PLAYER_ACTION, Keyboard::Num9, 0);
	m_inputManager->bind(NEXT_PLAYER_ACTION, Keyboard::Num9, 1);

	m_inputManager->bind(NEXT_UNIT_ACTION, Keyboard::Num0, 0);
	m_inputManager->bind(NEXT_UNIT_ACTION, Keyboard::Num0, 1);

	m_inputManager->bind(MOVE_ABILITY_ACTION, Keyboard::Num8, 0);
	m_inputManager->bind(MOVE_ABILITY_ACTION, Keyboard::Num8, 1);
}
