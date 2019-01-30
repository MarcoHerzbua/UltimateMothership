#pragma once
#include "stdafx.h"

#include "IGameComponent.h"

class GameObject;
class SteeringComponent;

class CursorComponent : public IGameComponent
{
public:
	CursorComponent(GameObject* gameObject);
	CursorComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void exit() override;

	void initTmxData() override;

	void updateCursor(const float deltaTimeSeconds);


protected:

	SteeringComponent* m_steering;

};