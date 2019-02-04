#pragma region include

#pragma once
#include "stdafx.h"
#include "GUIRenderComponent.h"

// abstract
#include "IGameComponent.h"

// enums

// forward declaration
class Game;
class GameObject;
class IGameEvent;
#pragma endregion


class IGUIWidgetComponent : public IGameComponent
{
public:
	IGUIWidgetComponent(GameObject* gameObject);
	IGUIWidgetComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual void update(const float deltaTimeSeconds) = 0;
	virtual void exit();

	virtual void init() = 0;
	virtual void initTmxData() override;

	tgui::Widget::Ptr getWidget() { return m_widget; };
	string getWidgetName() { return m_widgetName; };
	sf::Vector2f getWidgetSize() { return m_widget->getSize(); };
	sf::Vector2f getWidgetPosition() { return m_widget->getPosition(); };

	virtual void setWidgetText(sf::String s);

	virtual void setActive();
	virtual void setInactive();
	void onActivation();
protected:
	string m_widgetName;
	tgui::Widget::Ptr m_widget;
	GUIRenderComponent * m_guiRenderComponent;
	vector<GameEvents> m_events;
};