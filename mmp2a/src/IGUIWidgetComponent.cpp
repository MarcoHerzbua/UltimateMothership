#pragma region include

#include "stdafx.h"
#include "IGUIWidgetComponent.h"

// game classes
#include "Game.h"
#include "GameObject.h"

#pragma endregion

IGUIWidgetComponent::IGUIWidgetComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
}

IGUIWidgetComponent::IGUIWidgetComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
}

void IGUIWidgetComponent::exit()
{
	for (auto *e : m_events)
		delete e;
}

void IGUIWidgetComponent::initTmxData()
{
	auto cmp = m_gameObject->findComponents(GUI_RENDER_COMPONENT)[0];
	auto guiRenderCmp = static_cast<GUIRenderComponent *>(cmp);
	m_guiRenderComponent = guiRenderCmp;
	//name of the Component in Tiled == the name in the code
	//the widget gets saved in a tgui::Gui object and can later be found with this name
	m_widgetName = m_mapObject->name;
}


void IGUIWidgetComponent::setActive()
{
	//Increases Size of Widget to identify is as active
	auto widgetSize = getWidgetSize();
	auto widgetPos = getWidgetPosition();
	auto widgetOffset = widgetSize / 50.f;

	m_widget->setSize(widgetSize.x + widgetOffset.x, widgetSize.y + widgetOffset.y);
	m_widget->setPosition(widgetPos.x - widgetOffset.x / 2, widgetPos.y - widgetOffset.y / 2);
}

void IGUIWidgetComponent::setInactive()
{
	auto widgetSize = getWidgetSize();
	auto widgetPos = getWidgetPosition();
	auto widgetOffset = widgetSize / 50.f;

	m_widget->setSize(widgetSize.x - widgetOffset.x, widgetSize.y - widgetOffset.y);
	m_widget->setPosition(widgetPos.x + widgetOffset.x / 2, widgetPos.y + widgetOffset.y / 2);
}

void IGUIWidgetComponent::onActivation()
{
	for (auto *e : m_events)
	{
		Eventbus::getInstance().fireEvent(e);
	}
}

