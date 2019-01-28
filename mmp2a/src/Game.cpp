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

	m_gameStateManager = &GameStateManager::getInstance();
	m_inputManager = &InputManager::getInstance();
	m_gameObjectManager = &GameObjectManager::getInstance();
	m_renderManager = &RenderManager::getInstance();
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
	m_window.clear();

	m_renderManager->draw(&m_window);

	m_window.display();
}

void Game::shutdown()
{
	m_gameStateManager->exit();
}

void Game::bindKeys()
{
	m_inputManager->bind(EXIT_ACTION, Keyboard::Escape, 0);
	m_inputManager->bind(SWITCH_STATE_ACTION, Keyboard::Space, 0);

	m_inputManager->bind(MOVE_UP_ACTION, Keyboard::W, 0);
	m_inputManager->bind(MOVE_LEFT_ACTION, Keyboard::A, 0);
	m_inputManager->bind(MOVE_DOWN_ACTION, Keyboard::S, 0);
	m_inputManager->bind(MOVE_RIGHT_ACTION, Keyboard::D, 0);

	m_inputManager->bind(MOVE_UP_ACTION, Keyboard::Up, 1);
	m_inputManager->bind(MOVE_LEFT_ACTION, Keyboard::Left, 1);
	m_inputManager->bind(MOVE_DOWN_ACTION, Keyboard::Down, 1);
	m_inputManager->bind(MOVE_RIGHT_ACTION, Keyboard::Right, 1);

	m_inputManager->bind(SWITCH_HUMAN_AI, Keyboard::Num1, 0);
	m_inputManager->bind(SWITCH_HUMAN_AI, Keyboard::Num2, 1);
}
