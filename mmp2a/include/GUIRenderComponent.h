#pragma region include

#pragma once
#include "stdafx.h"

// abstract
#include "RenderComponent.h"
#include "IGameComponent.h"

// enums
#include "GameComponents.h"

// forward declaration
class Game;
class GameObject;
class IGUIWidgetComponent;

#pragma endregion

class GUIRenderComponent : public RenderComponent
{
public:
	GUIRenderComponent(GameObject* gameObject);
	GUIRenderComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow* window) override;
	void exit() override;
	void setScale(const float scale) override;

	void initTmxData() override;

	void addWidgetComponent(IGUIWidgetComponent * widget);
	void removeWidgetComponent(IGUIWidgetComponent * widget);
	vector<IGUIWidgetComponent *> findWidgetComponents(GameComponents cId);
	vector<IGUIWidgetComponent *>::iterator findWidgetComponentIterator(IGUIWidgetComponent * widget);

	void setWidgetActive(IGUIWidgetComponent * widget);
	void setNextWidgetActive();
	void setPreviousWidgetActive();
private:
	tgui::Gui * m_gui;
	shared_ptr<tgui::Theme> m_theme;
	vector<IGUIWidgetComponent *> m_widgets;

	IGUIWidgetComponent * m_activeWidget;
};