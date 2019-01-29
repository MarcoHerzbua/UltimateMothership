#pragma once

#include "stdafx.h"
#include "IAbilityComponent.h"

class AttackAbilityComponent : public IAbilityComponent
{
public:
	AttackAbilityComponent() = default;
	AttackAbilityComponent(GameObject* gameObject);
	AttackAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual ~AttackAbilityComponent() = default;

	virtual void update(const float deltaTime) override = 0;

};