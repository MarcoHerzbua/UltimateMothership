#include "stdafx.h"
#include "GUIInputComponent.h"
#include "GUISteeringComponent.h"
#include "Direction.h"
#include "GameEvents.h"
#include "GameEventClasses.h"
#include "SteeringComponent.h"
#include "InputManager.h"
#include "Eventbus.h"

GUIInputComponent::GUIInputComponent(GameObject * gameObject, IControllerComponent * controllerComponent)
	: HumanInputComponent(gameObject, controllerComponent)
{
	m_id = GUI_INPUT_COMPONENT;
}

GUIInputComponent::GUIInputComponent(GameObject * gameObject, IControllerComponent * controllerComponent, NLTmxMapObject & mapObject)
	:HumanInputComponent(gameObject, controllerComponent, mapObject)
{
	m_id = GUI_INPUT_COMPONENT;
}

void GUIInputComponent::update(const float deltaTimeSeconds)
{
	if (m_doAction)
		m_doAction(deltaTimeSeconds);
}

void GUIInputComponent::init(InputActions action)
{	
	m_steeringComp = static_cast<GUISteeringComponent*>(m_gameObject->findComponents(GUI_STEERING_COMPONENT)[0]);

	m_doAction = generateFunction(action);

	m_steeringComp->setTimeSinceLastInput(0);
}

void GUIInputComponent::initTmxData()
{
	HumanInputComponent::initTmxData();
}

void GUIInputComponent::exit()
{
}


function<void(float)> GUIInputComponent::generateFunction(InputActions action)
{
	//Direction dir = inputActionsToDirection(action);
	GameEvents event = inputToGameEvents(action);
	if (event == NULL_GAME_EVENT) err() << "NULL_GAME_EVENT when creating Event in GUIInputComponent\n";

	auto function = [steeringComp = this->m_steeringComp, action, event]
	(const float deltaTime) -> void {
		if (steeringComp->getTimeSinceLastInput() >= steeringComp->getTimeDelay()
			&& InputManager::getInstance().isKeyPressed(action, steeringComp->getPlayerIndex()))
		{
			steeringComp->setTimeSinceLastInput(0);
			
			Eventbus::getInstance().fireEvent(new MenuNavigationEvent(event));
		}
	};

	return function;
}
