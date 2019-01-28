#pragma region include

#include "stdafx.h"
#include "GUILabelComponent.h"
#include "GameEventClasses.h"

// game classes
#include "Game.h"
#include "GameObject.h"

#pragma endregion

GUILabelComponent::GUILabelComponent(GameObject * gameObject)
	: IGUIWidgetComponent(gameObject)
{
	m_id = GUI_LABEL_COMPONENT;
}

GUILabelComponent::GUILabelComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGUIWidgetComponent(gameObject, mapObject)
{
	m_id = GUI_LABEL_COMPONENT;
}

void GUILabelComponent::update(const float deltaTimeSeconds)
{
}

void GUILabelComponent::exit()
{
	IGUIWidgetComponent::exit();
}

void GUILabelComponent::init()
{
}

void GUILabelComponent::initTmxData()
{
	IGUIWidgetComponent::initTmxData();

	m_widget = tgui::Label::create();
	auto label = static_pointer_cast<tgui::Label>(m_widget);

	label->setPosition(m_mapObject->x, m_mapObject->y);
	label->setSize(m_mapObject->width, m_mapObject->height);

	string path = GameObjectManager::getInstance().getAssetPath();
	string text = "This is a placeholder text!";
	sf::Color color = sf::Color(255, 255, 255);


	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "Text")
		{
			text = property->value;
		}
	}

	//if (!m_font.loadFromFile(path))
	//{
	//	err() << "Font not loaded\n";
	//	return;
	//}

	label->setText(text);
	m_guiRenderComponent->addWidgetComponent(this);
	m_mapObject = nullptr;

}
