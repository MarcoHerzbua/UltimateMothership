
#pragma region include
#include "stdafx.h"
#include "ControlsState.h"

#include "GameObjectManager.h"
#include "GameStateManager.h"
#include "TmxLoader.h"
#pragma endregion

ControlsState::ControlsState()
{
	m_id = GameStates::CONTROLS_STATE;

	GameStateManager::getInstance().registerState(GameStates::CONTROLS_STATE, this);
}

void ControlsState::init()
{
	IGameState::init();

	TmxLoader::loadTmxFile("ControlsMap.tmx", sf::Vector2f());
}

void ControlsState::exit()
{
	IGameState::exit();

	//Eventbus::getInstance().removeListener(this);
}

void ControlsState::update(const float deltaTimeSeconds)
{
	m_gameObjectManager->update(deltaTimeSeconds);

	handleKeyInput();
}


void ControlsState::handleKeyInput()
{
}