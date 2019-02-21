#pragma region include

#include "stdafx.h"
#include "HumanInputComponent.h"

#include "GameObject.h"
#include "SteeringComponent.h"

#include "InputManager.h"
#include "Node.h"

#pragma endregion

HumanInputComponent::HumanInputComponent(GameObject * gameObject, IControllerComponent* controllerComponent)
	: IInputComponent(gameObject, controllerComponent)
{
	m_id = HUMAN_INPUT_COMPONENT;
}

HumanInputComponent::HumanInputComponent(GameObject * gameObject, IControllerComponent* controllerComponent, NLTmxMapObject & mapObject)
	: IInputComponent(gameObject, controllerComponent, mapObject)
{
	m_id = HUMAN_INPUT_COMPONENT;
}

void HumanInputComponent::update(const float deltaTimeSeconds)
{
	if (m_doAction)
		m_doAction(deltaTimeSeconds);
}

void HumanInputComponent::exit()
{
}

// TODO maybe call init from initTmxData
void HumanInputComponent::init(const InputActions action)
{
	m_steeringComp = static_cast<SteeringComponent*>(m_gameObject->findComponents(STEERING_COMPONENT)[0]);

	m_doAction = generateFunction(action);

	m_steeringComp->setTimeSinceLastInput(0);
}

void HumanInputComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}

function<void(float)> HumanInputComponent::generateFunction(InputActions action)
{
	Direction dir = inputActionsToDirection(action);

	auto function = [steeringComp = this->m_steeringComp, action, dir]
		(const float deltaTime) -> void {
			if (steeringComp->getTimeSinceLastInput() >= steeringComp->getTimeDelay()
				&& InputManager::getInstance().isActionActive(action, steeringComp->getPlayerIndex()))
			{
				Node* currentNode = steeringComp->getCurrentNode();
				Node* targetNode = currentNode->getTargetNode(dir);

				if (targetNode)
				{
					steeringComp->setCurrentNode(targetNode);

					steeringComp->setTimeSinceLastInput(0);
				}
			}
		};

	return function;
}
