#pragma once

#include "stdafx.h"
#include "AttackAbilityComponent.h"

class UltimateAttackAbilityComponent : public AttackAbilityComponent
{
public:
	UltimateAttackAbilityComponent(GameObject* gameObject);
	UltimateAttackAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;

};