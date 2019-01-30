#pragma once

#include "stdafx.h"

#include "NLTmxMap.h"
#include "Abilities.h"

#include "Stats.h"

#include "HelperMethods.h"

class ShipComponent;
class GameObject;

using namespace hm;

class IAbilityComponent
{
public:
	IAbilityComponent() = default;
	IAbilityComponent(GameObject* gameObject);
	IAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~IAbilityComponent() = default;

	virtual void exit();

	virtual void update(const float deltaTime) = 0;

	virtual void initTmxData();

	void addTarget(Target t);
	void resolveTargets();
	virtual void useAbility(Target t) = 0;
	

	Abilities getId() { return m_id; };
	GameObject* getGameObjectPtr() { return m_gameObject; };

	int getRange() { return m_range; };

protected:
	Abilities m_id;
	GameObject* m_gameObject;
	NLTmxMapObject* m_mapObject;

	vector<Target> m_targets;

	int m_range;

	void clearTargets();
};