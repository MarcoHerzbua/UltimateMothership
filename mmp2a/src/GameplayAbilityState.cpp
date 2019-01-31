#include "stdafx.h"
#include "GameplayAbilityState.h"
#include "CursorComponent.h"
#include "SteeringComponent.h"
#include "GameObjects.h"
#include "IAbilityComponent.h"
#include "Stats.h"
#include "MotherShipComponent.h"

GameplayAbilityState::GameplayAbilityState()
{
	m_id = ABILITY_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);
}

void GameplayAbilityState::init()
{
	IGameplayState::init();
}

void GameplayAbilityState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayAbilityState::exit()
{
}

void GameplayAbilityState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		auto cursorNode = playerMng->getCursor()->getCurrentNode();
		auto distanceToActive = playerMng->getCursor()->getDistanceToActive();
		auto attackRange = playerMng->getActiveShip()->getAbilityComponent(BASIC_ATTACK_ABILITY)->getRange();

		if (attackRange >= distanceToActive)
		{
			if (!cursorNode->isNodeOccupied())
			{
				Eventbus::getInstance().fireEvent(
					new GameplayStateChangeEvent(this, this));
				Eventbus::getInstance().fireEvent(
					new UpdatePopupEvent("There is nothing here to attack!!"));
				return;
			}

			GameObjects activeShipId = playerMng->getActiveShip()->getGameObjectPtr()->getId();
			vector<GameObjects> possibleEnemyShipIds = getPossibleEnemyShipIDs(activeShipId);

			GameObject * enemyShip = nullptr;
			for (GameObjects go : possibleEnemyShipIds)
			{
				enemyShip = cursorNode->getGameObject(go);
				if (enemyShip) //nullptr means no Object of this type found
				{
					Target t = { playerMng->getActiveShip()->getGameObjectPtr(), enemyShip };
					playerMng->getActiveShip()->addTarget(t, BASIC_ATTACK_ABILITY);

					Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(playerMng->getActiveShip()));
					Eventbus::getInstance().fireEvent(
						new GameplayStateChangeEvent(this, m_gameplayStateManager->getState(ATTACK_GAMEPLAY_STATE)));
					Eventbus::getInstance().fireEvent(
						new UpdatePopupEvent("You are about to attack an enemy!! Continue?"));
					return;
				}
			}

			Eventbus::getInstance().fireEvent(
				new GameplayStateChangeEvent(this, this));
			Eventbus::getInstance().fireEvent(
				new UpdatePopupEvent("There is no enemy ship here to attack!!"));
			return;
		}

	}
	if (InputManager::getInstance().isActionActive(X_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		auto motherShip = dynamic_cast<MotherShipComponent*>(playerMng->getActiveShip());
		if (!motherShip)
		{
			Eventbus::getInstance().fireEvent(new GameplayStateChangeEvent(this, this));
			Eventbus::getInstance().fireEvent(new UpdatePopupEvent("Select your mothership first if you want to cast an ultimate"));
			return;
		}

		auto cursorNode = playerMng->getCursor()->getCurrentNode();
		auto distanceToActive = playerMng->getCursor()->getDistanceToActive();
		auto attackRange = playerMng->getActiveShip()->getAbilityComponent(ULTIMATE_ATTACK_ABILITY)->getRange();

		if (attackRange >= distanceToActive)
		{
			if (!cursorNode->isNodeOccupied())
			{
				Eventbus::getInstance().fireEvent(
					new GameplayStateChangeEvent(this, this));
				Eventbus::getInstance().fireEvent(
					new UpdatePopupEvent("There is nothing here to attack!!"));
				return;
			}

			GameObjects activeShipId = playerMng->getActiveShip()->getGameObjectPtr()->getId();
			vector<GameObjects> possibleEnemyShipIds = getPossibleEnemyShipIDs(activeShipId);

			GameObject * enemyShip = nullptr;
			for (GameObjects go : possibleEnemyShipIds)
			{
				enemyShip = cursorNode->getGameObject(go);
				if (enemyShip) //nullptr means no Object of this type found
				{
					Target t = { playerMng->getActiveShip()->getGameObjectPtr(), enemyShip };
					playerMng->getActiveShip()->addTarget(t, ULTIMATE_ATTACK_ABILITY);

					Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(playerMng->getActiveShip()));
					Eventbus::getInstance().fireEvent(
						new GameplayStateChangeEvent(this, m_gameplayStateManager->getState(ATTACK_GAMEPLAY_STATE)));
					Eventbus::getInstance().fireEvent(
						new UpdatePopupEvent("You are about to use an Ultimate on an enemy!! Continue?"));
					return;
				}
			}

			Eventbus::getInstance().fireEvent(
				new GameplayStateChangeEvent(this, this));
			Eventbus::getInstance().fireEvent(
				new UpdatePopupEvent("There is no enemy ship here to attack!!"));
			return;
		}

	}

	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(SELECTION_GAMEPLAY_STATE);
	}

}

vector<GameObjects> GameplayAbilityState::getPossibleEnemyShipIDs(GameObjects go)
{
	vector<GameObjects> possibleEnemyShipIds;
	switch (go)
	{
	case P1_FARMER_OBJECT:
	case P1_FIGHTER_OBJECT:
	case P1_MOTHER_OBJECT:
	{
		possibleEnemyShipIds = { P2_FARMER_OBJECT, P2_FIGHTER_OBJECT, P2_MOTHER_OBJECT };
	}
	break;
	case P2_FIGHTER_OBJECT:
	case P2_MOTHER_OBJECT:
	case P2_FARMER_OBJECT:
	{
		possibleEnemyShipIds = { P1_FARMER_OBJECT, P1_FIGHTER_OBJECT, P1_MOTHER_OBJECT };
	}
	break;
	default:
		err() << "Current Ship does not have a GameObject ID when Attacking";
		break;
	}
	return possibleEnemyShipIds;
}


