#pragma once

#include "stdafx.h"
#include "ShipComponent.h"

class FarmShipComponent : public ShipComponent
{
public:
	FarmShipComponent(GameObject* gameObject);
	FarmShipComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;

	void initBaseStats() override;

	void initTmxData() override;

protected:
};