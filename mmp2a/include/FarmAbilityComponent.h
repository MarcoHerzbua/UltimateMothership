#pragma once

#include "stdafx.h"
#include "IAbilityComponent.h"

class FarmAbilityComponent : public IAbilityComponent
{
public:
	FarmAbilityComponent(GameObject* gameObject);
	FarmAbilityComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;

};