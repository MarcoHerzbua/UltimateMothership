
#pragma region include
#include "stdafx.h"
#include "CreditsState.h"

// game classes
#include "Game.h"
#include "GameObject.h"

// components
#include "SpriteRenderComponent.h"
#include "GUIRenderComponent.h"

// singleton
#include "InputManager.h"
#include "GameStateManager.h"
#include "TmxLoader.h"
#pragma endregion

CreditsState::CreditsState()
{
	m_id = GameStates::CREDITS_STATE;

	GameStateManager::getInstance().registerState(GameStates::CREDITS_STATE, this);
}

void CreditsState::init()
{
	IGameState::init();

	TmxLoader::loadTmxFile("Credits.tmx", sf::Vector2f());
}

void CreditsState::exit()
{
	IGameState::exit();

	//Eventbus::getInstance().removeListener(this);
}

void CreditsState::update(const float deltaTimeSeconds)
{
	m_gameObjectManager->update(deltaTimeSeconds);

	handleKeyInput();
}


void CreditsState::handleKeyInput()
{
	//if (m_inputManager->isKeyPressed(InputActions::B_BUTTON_ACTION, 0))
	//{
	//	RenderWindow * window = m_gameStateManager->getGamePtr()->getWindowPtr();
	//	window->close();
	//}

	//if (m_inputManager->isKeyPressed(InputActions::CONFIRM_ACTION, 0))
	//{
	//	m_gameStateManager->setState(GameStates::MAIN_STATE);
	//}
}