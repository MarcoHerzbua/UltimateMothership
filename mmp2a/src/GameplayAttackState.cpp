#include "stdafx.h"
#include "GameplayAttackState.h"
#include "CursorComponent.h"
#include "SteeringComponent.h"
#include "GameObjects.h"
#include "IAbilityComponent.h"
#include "Stats.h"
#include "MotherShipComponent.h"
#include "BasicAttackAbilityComponent.h"

GameplayAttackState::GameplayAttackState()
{
	m_id = ATTACK_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);

}

void GameplayAttackState::init()
{
	IGameplayState::init();
}

void GameplayAttackState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayAttackState::exit()
{
}

void GameplayAttackState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();
	auto abilitiy = static_cast<BasicAttackAbilityComponent*>(playerMng->getActiveShip()->getAbilityComponent(BASIC_ATTACK_ABILITY));

	playerMng->getCursor()->setPossibleRange(abilitiy->getRange());

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
					
					auto enemyShipComp = getShipFromGameObject(enemyShip);
					auto shipStats = playerMng->getActiveShip()->getCurrentStats();
					int damage = enemyShipComp->calcDamage(abilitiy->getBaseDamage(), shipStats.attack);
					string damageString = std::to_string(damage) + " Damage!!";
					
					//decrease Movement to 0
					playerMng->getActiveShip()->decreasMovement(playerMng->getActiveShip()->getCurrentMovement());

					playerMng->getActiveShip()->resolveTargets();

					Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(playerMng->getActiveShip()));
					Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(enemyShipComp));
					Eventbus::getInstance().fireEvent(
						new GameplayStateChangeEvent(this, m_gameplayStateManager->getState(SELECTION_GAMEPLAY_STATE)));
					Eventbus::getInstance().fireEvent(
						new UpdatePopupEvent("Your attack was successful!! You did " + damageString));
					playerMng->activateNextUnit();
					return;
				}
			}

			Eventbus::getInstance().fireEvent(
				new GameplayStateChangeEvent(this, this));
			Eventbus::getInstance().fireEvent(
				new UpdatePopupEvent("There is no enemy ship here to attack!!"));
			return;
		}

		Eventbus::getInstance().fireEvent(
			new GameplayStateChangeEvent(this, this));
		Eventbus::getInstance().fireEvent(
			new UpdatePopupEvent("The target is out of attack range!!"));
	}
	if (InputManager::getInstance().isActionActive(B_BUTTON_ACTION, playerMng->getActivePlayer()))
	{
		m_gameplayStateManager->setState(ABILITY_GAMEPLAY_STATE);
	}


}

vector<GameObjects> GameplayAttackState::getPossibleEnemyShipIDs(GameObjects go)
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


