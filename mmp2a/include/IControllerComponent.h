#pragma region include

#pragma once
#include "stdafx.h"

#include "ControllerComponents.h"

class GameObject;
class NLTmxMapObject;
class SteeringComponent;

using namespace std;
using namespace sf;
#pragma endregion

class IControllerComponent
{
public:
	IControllerComponent() = default;
	IControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent);
	IControllerComponent(GameObject* gameObject, SteeringComponent* steeringComponent, NLTmxMapObject& mapObject);

	virtual ~IControllerComponent() = default;

	virtual void exit() = 0;
	virtual void update(const float deltaTime) = 0;

	virtual void initTmxData() = 0;

	ControllerComponents getId() { return m_id; };
	GameObject* getGameObjectPtr() { return m_gameObject; };
	SteeringComponent* getSteeringComponent() { return m_steeringComponent; };

protected:
	ControllerComponents m_id;
	GameObject* m_gameObject;
	SteeringComponent* m_steeringComponent;
	NLTmxMapObject* m_mapObject;
};
