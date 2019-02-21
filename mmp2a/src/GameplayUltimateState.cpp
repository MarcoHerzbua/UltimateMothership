#include "stdafx.h"
#include "GameplayUltimateState.h"

#include "IAbilityComponent.h"
#include "SteeringComponent.h"
#include "MotherShipComponent.h"
#include "UltimateAttackAbilityComponent.h"
#include "CursorComponent.h"

#include "GameplayStateManager.h"
#include "PlayerManager.h"
#include "InputManager.h"
#include "Eventbus.h"

#include "GameEventClasses.h"
#include "Stats.h"
#include "Node.h"
#include "GameObject.h"

GameplayUltimateState::GameplayUltimateState()
{
	m_id = ULTIMATE_GAMEPLAY_STATE;

	GameplayStateManager::getInstance().registerState(m_id, this);
}

void GameplayUltimateState::init()
{
	IGameplayState::init();
}

void GameplayUltimateState::update(const float deltaTimeSeconds)
{
	handleKeyInput();
}

void GameplayUltimateState::exit()
{
}

void GameplayUltimateState::handleKeyInput()
{
	auto playerMng = &PlayerManager::getInstance();
	auto motherShip = dynamic_cast<MotherShipComponent*>(playerMng->getActiveShip());
	if (!motherShip)
	{
		auto abilityState = m_gameplayStateManager->getState(ABILITY_GAMEPLAY_STATE);
		Eventbus::getInstance().fireEvent(new GameplayStateChangeEvent(abilityState, abilityState));
		Eventbus::getInstance().fireEvent(new UpdatePopupEvent("Select your mothership first if you want to cast an ultimate"));
		return;
	}

	auto ability = static_cast<UltimateAttackAbilityComponent*>(motherShip->getAbilityComponent(ULTIMATE_ATTACK_ABILITY));

	playerMng->getCursor()->setPossibleRange(ability->getRange());

	if (InputManager::getInstance().isActionActive(A_BUTTON_ACTION, playerMng->getActivePlayer()))
	{

		auto cursorNode = playerMng->getCursor()->getCurrentNode();
		auto distanceToActive = playerMng->getCursor()->getDistanceToActive();
		auto attackRange = ability->getRange();

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
					//TODO: UlitmateCosts are hardcoded at the moment
					if (playerMng->getRessources(playerMng->getActivePlayer()) < 12)
					{
						Eventbus::getInstance().fireEvent(new GameplayStateChangeEvent(this, this));
						Eventbus::getInstance().fireEvent(new UpdatePopupEvent("Not enough Resources to cast Ultimate!!"));
						return;
					}

					playerMng->decreaseRessources(playerMng->getActivePlayer(), 12);

					Target t = { playerMng->getActiveShip()->getGameObjectPtr(), enemyShip };
					playerMng->getActiveShip()->addTarget(t, ULTIMATE_ATTACK_ABILITY);

					auto enemyShipComp = getShipFromGameObject(enemyShip);
					auto shipStats = playerMng->getActiveShip()->getCurrentStats();
					int damage = enemyShipComp->calcDamage(ability->getBaseDamage(), shipStats.attack);
					string damageString = to_string(damage) + " Damage!!";

					//decrease Movement to 0
					playerMng->getActiveShip()->decreasMovement(playerMng->getActiveShip()->getCurrentMovement());

					playerMng->getActiveShip()->resolveTargets();

					Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(playerMng->getActiveShip()));
					Eventbus::getInstance().fireEvent(new UpdateShipStatsEvent(enemyShipComp));
					Eventbus::getInstance().fireEvent(
						new GameplayStateChangeEvent(this, m_gameplayStateManager->getState(SELECTION_GAMEPLAY_STATE)));
					Eventbus::getInstance().fireEvent(
						new UpdatePopupEvent("Your attack was successful!! You did " + damageString));
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
		m_gameplayStateManager->setState(ABILITY_GAMEPLAY_STATE);
	}

}

vector<GameObjects> GameplayUltimateState::getPossibleEnemyShipIDs(GameObjects go)
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


