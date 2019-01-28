#pragma region include

#include "stdafx.h"
#include "AiInputComponent.h"

#include "AIControllerComponent.h"

#include "GameObject.h"
#include "IGameComponent.h"
#include "SteeringComponent.h"

#include "NodeGraphRenderComponent.h"

#include "InputManager.h"

#pragma endregion

AiInputComponent::AiInputComponent(GameObject * gameObject, IControllerComponent* controllerComponent)
	: IInputComponent(gameObject, controllerComponent)
{
	m_id = AI_INPUT_COMPONENT;
}

AiInputComponent::AiInputComponent(GameObject * gameObject, IControllerComponent* controllerComponent, NLTmxMapObject & mapObject)
	: IInputComponent(gameObject, controllerComponent, mapObject)
{
	m_id = AI_INPUT_COMPONENT;
}

void AiInputComponent::update(const float deltaTimeSeconds)
{
	if (m_action == NULL_ACTION)
		m_action = static_cast<AIControllerComponent*>(m_controllerComponent)->getNextActionFromStack();

	if (m_action != NULL_ACTION && m_doAction)
		m_doAction(deltaTimeSeconds, &m_action);
}

void AiInputComponent::exit()
{
}

void AiInputComponent::init()
{
	m_steeringComp = static_cast<SteeringComponent*>(m_gameObject->findComponents(STEERING_COMPONENT)[0]);

	m_doAction = generateFunction();

	m_action = NULL_ACTION;

	m_steeringComp->setTimeSinceLastInput(0);
}

void AiInputComponent::initTmxData()
{
	if (!m_mapObject)
		return;

	m_mapObject = nullptr;
}

function<void(float, InputActions*)> AiInputComponent::generateFunction()
{
	auto function = [steeringComp = this->m_steeringComp]
		(const float deltaTime, InputActions* action) -> void {
			Direction dir = inputActionsToDirection(*action);

			if (steeringComp->getTimeSinceLastInput() >= steeringComp->getTimeDelay())
			{
				Node* currentNode = steeringComp->getCurrentNode();
				Node* targetNode = currentNode->getTargetNode(dir);

				if (targetNode)
				{
					steeringComp->setCurrentNode(targetNode);

					steeringComp->setTimeSinceLastInput(0);
				}

				*action = NULL_ACTION;
			}
		};

	return function;
}
