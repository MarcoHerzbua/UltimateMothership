#pragma once

#include "stdafx.h"
#include "AttackAbilityComponent.h"

class BasicAttackAbilityComponent : public AttackAbilityComponent
{
public:
	BasicAttackAbilityComponent(GameObject* gameObject);
	BasicAttackAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;

	void useAbility(Target t) override;
private:
	static constexpr int m_baseDamage = 10;

	int getBaseDamage() override { return m_baseDamage; };
};