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
	auto currIt = wIt;

	if (wIt == m_widgets.end())
		currIt = m_widgets.begin();
	else
		++currIt;

	//iterate through widgets until a Button is found
	while(wIt != currIt)
	{
		if (currIt == m_widgets.end())
		{
			currIt = m_widgets.begin();
			continue;
		}

		if ((*currIt)->getId() == GUI_BUTTON_COMPONENT)
		{
			setWidgetActive(*currIt);
			return;
		}
		++currIt;
	}

	err() << "No Buttons for navigation found in GUI\n";
}

void GUIRenderComponent::setPreviousWidgetActive()
{
	auto wIt = findWidgetComponentIterator(m_activeWidget);
	auto currIt = wIt;

	if (wIt == m_widgets.begin())
		currIt = --m_widgets.end();
	else
		--currIt;

	//iterate through widgets until a Button is found
	while (wIt != currIt)
	{
		if (currIt == m_widgets.begin())
		{
			if ((*currIt)->getId() == GUI_BUTTON_COMPONENT)
			{
				setWidgetActive(*currIt);
				return;
			}

			currIt = --m_widgets.end();
			continue;
		}

		if ((*currIt)->getId() == GUI_BUTTON_COMPONENT)
		{
			setWidgetActive(*currIt);
			return;
		}
		--currIt;
	}

	err() << "No Buttons for navigation found in GUI\n";

}

void GUIRenderComponent::update(const float deltaTimeSeconds)
{


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

void GUIRenderComponent::onEvent(IGameEvent * event)
{
	switch (event->getID())
	{
	case(NAVIGATE_DOWN_EVENT):
	{
		setNextWidgetActive();
	}
	break;
	case(NAVIGATE_UP_EVENT):
	{
		setPreviousWidgetActive();
	}
	break;
	case(CONFIRM_EVENT):
	{
		if (m_activeWidget)
			m_activeWidget->onActivation();
	}
	break;
	case(UPDATE_SHIPSTATS_EVENT):
	{
		auto ev = dynamic_cast<UpdateShipStatsEvent*>(event);
		auto stats = ev->m_shipComponent->getCurrentStats();

		auto widget = static_pointer_cast<tgui::Label>(m_gui->get("P1HPStats"));
		widget->setText(to_string(stats.life));
		widget = static_pointer_cast<tgui::Label>(m_gui->get("P1AtkStats"));
		widget->setText(to_string(stats.attack));
		widget = static_pointer_cast<tgui::Label>(m_gui->get("P1DefStats"));
		widget->setText(to_string(stats.defense));
		widget = static_pointer_cast<tgui::Label>(m_gui->get("P1MoveStats"));
		widget->setText(to_string(stats.movement));
	}
	break;
	case(UPDATE_PLAYERSTATS_EVENT):
	{
		auto ev = dynamic_cast<UpdatePlayerStatsEvent*>(event);
		auto widget = static_pointer_cast<tgui::Label>(m_gui->get("P1ResourceStats"));
		widget->setText(to_string(ev->m_resources));
	}
	break;
	case(UPDATE_BUTTONMAP_EVENT):
	{
		auto ev = dynamic_cast<UpdateButtonMapEvent*>(event);
		auto widget = static_pointer_cast<tgui::Label>(m_gui->get("ButtonOneText"));
		widget->setText(ev->m_buttonMap[0]);
		widget = static_pointer_cast<tgui::Label>(m_gui->get("ButtonTwoText"));
		widget->setText(ev->m_buttonMap[1]);
		widget = static_pointer_cast<tgui::Label>(m_gui->get("ButtonThreeText"));
		widget->setText(ev->m_buttonMap[2]);
		widget = static_pointer_cast<tgui::Label>(m_gui->get("ButtonFourText"));
		widget->setText(ev->m_buttonMap[3]);

	}
	default:
		break;
	}
}

