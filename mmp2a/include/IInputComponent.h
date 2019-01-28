#pragma region include

#pragma once
#include "stdafx.h"

#include "NLTmxMap.h"
#include "InputComponents.h"

class GameObject;
class IControllerComponent;

#pragma endregion

class IInputComponent
{
public:
	IInputComponent() = default;
	IInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent);
	IInputComponent(GameObject* gameObject, IControllerComponent* controllerComponent, NLTmxMapObject& mapObject);

	virtual ~IInputComponent() = default;

	virtual void exit() = 0;
	virtual void update(const float deltaTime) = 0;

	virtual void initTmxData() = 0;

	InputComponents getId() { return m_id; };
	GameObject* getGameObjectPtr() { return m_gameObject; };
	IControllerComponent* getControllerComponent() { return m_controllerComponent; };

protected:
	InputComponents m_id;
	GameObject* m_gameObject;
	IControllerComponent* m_controllerComponent;
	NLTmxMapObject* m_mapObject;
};