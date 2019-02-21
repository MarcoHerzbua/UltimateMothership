#pragma region include

#include "stdafx.h"
#include "GUIButtonComponent.h"

#include "GameEventClasses.h"
#include "GameObjectManager.h"
#include "NLTmxMap.h"
#include "GUIRenderComponent.h"


#pragma endregion

GUIButtonComponent::GUIButtonComponent(GameObject * gameObject)
	: IGUIWidgetComponent(gameObject)
{
	m_id = GUI_BUTTON_COMPONENT;
}

GUIButtonComponent::GUIButtonComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGUIWidgetComponent(gameObject, mapObject)
{
	m_id = GUI_BUTTON_COMPONENT;
}

void GUIButtonComponent::update(const float deltaTimeSeconds)
{
}

void GUIButtonComponent::exit()
{
	IGUIWidgetComponent::exit();
}

void GUIButtonComponent::init()
{
}

void GUIButtonComponent::initTmxData()
{
	IGUIWidgetComponent::initTmxData();

	m_widget = tgui::Button::create();
	auto button = static_pointer_cast<tgui::Button>(m_widget);

	button->setPosition(m_mapObject->x, m_mapObject->y);
	button->setSize(m_mapObject->width, m_mapObject->height);

	string path = GameObjectManager::getInstance().getAssetPath();
	string text = "";
	int textSize = 16;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "Text")
		{
			text = property->value;
		}
		if (name.substr(0, 5) == "Event")
		{
			auto event = stringToGameEvents(property->value);
			if (event == NULL_GAME_EVENT) err() << "NULL_GAME_EVENT when creating " << m_mapObject->name << "\n";
			m_events.push_back(event);
		}
		if (name == "TextSize")
			textSize = stoi(property->value);
		if (name == "isVisible")
			if (property->value == "false")
				button->setVisible(false);
	}

	//if (!m_font.loadFromFile(path))
	//{
	//	err() << "Font not loaded\n";
	//	return;
	//}

	button->setText(text);
	button->setTextSize(textSize);
	m_guiRenderComponent->addWidgetComponent(this);
	m_mapObject = nullptr;

}

void GUIButtonComponent::setActive()
{
	IGUIWidgetComponent::setActive();

	static_pointer_cast<tgui::Button>(m_widget)->getRenderer()->setTextColor(Color(255, 0, 0));
}

void GUIButtonComponent::setInactive()
{
	IGUIWidgetComponent::setInactive();

	static_pointer_cast<tgui::Button>(m_widget)->getRenderer()->setTextColor(Color(255, 255, 255));

}
