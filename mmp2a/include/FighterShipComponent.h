#pragma once

#include "stdafx.h"
#include "ShipComponent.h"

class FighterShipComponent : ShipComponent
{
public:
	FighterShipComponent(GameObject* gameObject);
	FighterShipComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;

	void initBaseStats() override;

	void initTmxData() override;

protected:
};