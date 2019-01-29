#pragma once

#include "stdafx.h"
#include "AttackAbilityComponent.h"

class BasicAttackAbilityComponent : public AttackAbilityComponent
{
public:
	BasicAttackAbilityComponent(GameObject* gameObject);
	BasicAttackAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;

};