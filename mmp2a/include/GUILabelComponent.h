#pragma region include

#pragma once
#include "stdafx.h"

#include "IGUIWidgetComponent.h"

#pragma endregion

class GUILabelComponent : public IGUIWidgetComponent
{
public:
	GUILabelComponent(GameObject* gameObject);
	GUILabelComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTimeSeconds) override;
	void exit() override;

	void init() override;
	void initTmxData() override;

	void setWidgetText(sf::String s) override;
	void setTextColor(Color c);
private:
};