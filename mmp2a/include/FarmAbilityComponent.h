#pragma once

#include "stdafx.h"
#include "IAbilityComponent.h"

#include "ShipComponent.h"

class FarmAbilityComponent : public IAbilityComponent
{
public:
	FarmAbilityComponent(GameObject* gameObject);
	FarmAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;
	
	void useAbility(Target t) override;
};