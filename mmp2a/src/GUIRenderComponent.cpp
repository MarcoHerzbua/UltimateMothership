#pragma region include

#include "stdafx.h"
#include "GUIRenderComponent.h"
#include "IGUIWidgetComponent.h"
#include "Eventbus.h"
#include "GameEventClasses.h"

// game classes
#include "Game.h"
#include "GameObject.h"

#pragma endregion

GUIRenderComponent::GUIRenderComponent(GameObject * gameObject)
	: RenderComponent(gameObject)
{
	m_id = GUI_RENDER_COMPONENT;
	m_gui = new tgui::Gui();

}

GUIRenderComponent::GUIRenderComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: RenderComponent(gameObject, mapObject)
{
	m_id = GUI_RENDER_COMPONENT;
	m_gui = new tgui::Gui();
}

void GUIRenderComponent::initTmxData()
{
	string path = GameObjectManager::getInstance().getAssetPath();
	string font = "REFSAN.TTF";
	string theme = "Black.txt";

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "Path")
		{
			font = property->value;
		}
		if (name == "Theme")
		{
			theme = property->value;
		}
	}

	m_gui->setFont(path + font);
	m_theme = make_shared<tgui::Theme>(path + theme);
	tgui::Theme::setDefault(m_theme.get());

	m_mapObject = nullptr;
}

void GUIRenderComponent::addWidgetComponent(IGUIWidgetComponent * widget)
{
	m_gui->add(widget->getWidget(), widget->getWidgetName());
	m_widgets.insert(m_widgets.begin(), widget);

	if (!m_activeWidget)
		setWidgetActive(widget);
}

void GUIRenderComponent::removeWidgetComponent(IGUIWidgetComponent * widget)
{
	auto cIti = findWidgetComponentIterator(widget);
	m_gui->remove(widget->getWidget());

	if (cIti != m_widgets.end())
	{
		m_widgets.erase(cIti);
		(*cIti)->exit();
		delete (*cIti);
	}
}

vector<IGUIWidgetComponent*> GUIRenderComponent::findWidgetComponents(GameComponents cId)
{
	vector<IGUIWidgetComponent *> output;
	for (auto w : m_widgets)
	{
		if (w->getId() == cId)
			output.push_back(w);
	}
	return output;
}

vector<IGUIWidgetComponent*>::iterator GUIRenderComponent::findWidgetComponentIterator(IGUIWidgetComponent * widget)
{
	for (auto cIti = m_widgets.begin(); cIti != m_widgets.end(); cIti++)
	{
		if ((*cIti) == widget) 
			return cIti;
	}

	return m_widgets.end();
}

void GUIRenderComponent::setWidgetActive(IGUIWidgetComponent * widget)
{
	widget->setActive();
	if(m_activeWidget)
		m_activeWidget->setInactive();
	m_activeWidget = widget;
}

void GUIRenderComponent::setNextWidgetActive()
{
	auto wIt = findWidgetComponentIterator(m_activeWidget);
	++wIt;
	if (wIt == m_widgets.end())
		wIt = m_widgets.begin();

	setWidgetActive(*wIt);
}

void GUIRenderComponent::setPreviousWidgetActive()
{
	auto wIt = findWidgetComponentIterator(m_activeWidget);

	if (wIt == m_widgets.begin())
		wIt = --m_widgets.end();
	else
		--wIt;

	setWidgetActive(*wIt);
}

void GUIRenderComponent::update(const float deltaTimeSeconds)
{
	//TODO: for Testing!! Implement Input for MenuNavigation properly
	if (InputManager::getInstance().isKeyPressed(InputActions::MOVE_UP_ACTION, 0))
	{
		setPreviousWidgetActive();
	}

	if (InputManager::getInstance().isKeyPressed(InputActions::MOVE_DOWN_ACTION, 0))
	{
		setNextWidgetActive();
	}

	if (InputManager::getInstance().isKeyPressed(InputActions::SWITCH_STATE_ACTION, 0))
	{
		if (m_activeWidget)
			m_activeWidget->onActivation();
	}

	//if (InputManager::getInstance().isKeyPressed(InputActions::EXIT_ACTION, 0))
	//{
	//	Eventbus::getInstance().fireEvent(new ExitGameEvent());
	//}


}

void GUIRenderComponent::draw(sf::RenderWindow* window)
{

	m_gui->setTarget(*window);
	m_gui->draw();
}

void GUIRenderComponent::exit()
{
	m_gui->removeAllWidgets();
	for (auto w : m_widgets)
	{
		w->exit();
	}
	m_widgets.clear();
	delete m_gui;
	//TODO: m_theme is shared_ptr: Check if Object is deleted correctly
	//delete m_theme;
}

void GUIRenderComponent::setScale(const float scale)
{
}

