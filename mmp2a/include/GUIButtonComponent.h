#pragma region include

#pragma once
#include "stdafx.h"

#include "IGUIWidgetComponent.h"


using namespace std;
using namespace sf;
#pragma endregion

class GUIButtonComponent : public IGUIWidgetComponent
{
public:
	GUIButtonComponent(GameObject* gameObject);
	GUIButtonComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void exit() override;

	void init() override;
	void initTmxData() override;

	void setActive() override;
	void setInactive() override;
private:
};