#pragma once
#include "stdafx.h"

#include "IGameComponent.h"

#include "HelperMethods.h"

class SteeringComponent;

using namespace std;
using namespace sf;
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

	Node* getCurrentNode();
	int getDistanceToActive() { return m_distanceToActive; };

	int getPossibleRange() { return m_possibleRange; };
	void setPossibleRange(int range) { m_possibleRange = range; };
protected:

	SteeringComponent* m_steering;

	int m_distanceToActive;

	int m_possibleRange = 0;
};