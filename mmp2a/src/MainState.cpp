#pragma region include

#include "stdafx.h"
#include "MainState.h"

#include "GameplayAbilityState.h"
#include "GameplayAttackState.h"
#include "GameplayMoveState.h"
#include "GameplaySelectionState.h"
#include "GameplayTransitionState.h"
#include "GameplayEndTurnState.h"
#include "GameplayGameOverState.h"
#include "GameplayUltimateState.h"

#include "InputManager.h"
#include "GameStateManager.h"
#include "PlayerManager.h"
#include "GameplayStateManager.h"
#include "GameObjectManager.h"
#include "Eventbus.h"

#include "GameEventClasses.h"

#include "TmxLoader.h"


#pragma endregion

MainState::MainState()
{
	m_id = GameStates::MAIN_STATE;

	GameStateManager::getInstance().registerState(GameStates::MAIN_STATE, this);
}

void MainState::init()
{
	IGameState::init();

	m_playerManager->registerPlayer(0);
	m_playerManager->registerPlayer(1);

	TmxLoader::loadTmxFile("SpaceMap.tmx", Vector2f());
	// TmxLoader::loadTmxFile("SpaceMapTest.tmx", Vector2f());

	m_gameplayStateManager = &GameplayStateManager::getInstance();

	//states get registered automatically when constructed TODO thats what rado meant in the email
	auto abilityState = new GameplayAbilityState();
	auto attackState = new GameplayAttackState();
	auto moveState = new GameplayMoveState();
	auto selectState = new GameplaySelectionState();
	auto transitionState = new GameplayTransitionState();
	auto endTurnState = new GameplayEndTurnState();
	auto gameOverState = new GameplayGameOverState();
	auto ultimateState = new GameplayUltimateState();

	Eventbus::getInstance().fireEvent(new GameplayStateChangeEvent(selectState, selectState));
	Eventbus::getInstance().fireEvent(new UpdatePopupEvent("The Game is about to start! Player 1 goes first"));
	//Eventbus::getInstance().fireEvent(new TogglePopupEvent(true));

	//Eventbus::getInstance().fireEvent(new UpdatePlayerStatsEvent());
	//m_gameplayStateManager->setState(TRANSITION_GAMEPLAY_STATE);
}							

void MainState::update(const float deltaTimeSeconds)
{
	m_gameObjectManager->update(deltaTimeSeconds);
	m_playerManager->update(deltaTimeSeconds);
	m_gameplayStateManager->update(deltaTimeSeconds);

	handleKeyInput();
}

void MainState::exit()
{
	IGameState::exit();
	GameplayStateManager::getInstance().exit();
}


void MainState::handleKeyInput()
{
	if (m_inputManager->isActionActive(InputActions::ESCAPE_ACTION, 0))
	{
		m_gameStateManager->setState(GameStates::MENU_STATE);
	}
}

