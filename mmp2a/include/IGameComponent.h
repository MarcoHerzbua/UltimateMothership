#pragma region include

#pragma once
#include "stdafx.h"

#include "GameComponents.h"

class GameObject;
class NLTmxMapObject;

#pragma endregion

class IGameComponent
{
public:
	IGameComponent() = default;
	IGameComponent(GameObject* gameObject);
	IGameComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~IGameComponent() = default;

	virtual void exit() = 0;
	virtual void update(const float deltaTime) = 0;

	virtual void initTmxData() = 0;

	GameComponents getId() { return m_id; };
	GameObject* getGameObjectPtr() { return m_gameObject; };

protected:
	GameComponents m_id;
	GameObject* m_gameObject;
	NLTmxMapObject* m_mapObject;
};
