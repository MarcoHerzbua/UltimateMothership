#pragma once

#include "stdafx.h"
#include "ShipComponent.h"

class MotherShipComponent : public ShipComponent
{
public:
	MotherShipComponent(GameObject* gameObject);
	MotherShipComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;

	void initBaseStats() override;

	void initTmxData() override;

protected:
};