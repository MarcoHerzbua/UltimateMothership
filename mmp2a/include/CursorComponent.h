#pragma once
#include "stdafx.h"

#include "IGameComponent.h"

#include "HelperMethods.h"

class GameObject;
class SteeringComponent;

using namespace hm;

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

	int m_distanceToActive;
};