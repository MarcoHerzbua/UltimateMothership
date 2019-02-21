
#pragma region include

#include "stdafx.h"
#include "GUIPanelComponent.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "GUIRenderComponent.h"
#include "NLTmxMap.h"

#pragma endregion

GUIPanelComponent::GUIPanelComponent(GameObject * gameObject)
	: IGUIWidgetComponent(gameObject)
{
	m_id = GUI_PANEL_COMPONENT;
}

GUIPanelComponent::GUIPanelComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGUIWidgetComponent(gameObject, mapObject)
{
	m_id = GUI_PANEL_COMPONENT;
}

void GUIPanelComponent::update(const float deltaTimeSeconds)
{
}

void GUIPanelComponent::exit()
{
	IGUIWidgetComponent::exit();
}

void GUIPanelComponent::init()
{
}

void GUIPanelComponent::initTmxData()
{
	IGUIWidgetComponent::initTmxData();

	m_widget = tgui::Panel::create();
	auto panel = static_pointer_cast<tgui::Panel>(m_widget);

	panel->setPosition(m_mapObject->x, m_mapObject->y);
	panel->setSize(m_mapObject->width, m_mapObject->height);

	string path = GameObjectManager::getInstance().getAssetPath();
	string background = "checker32.png";
	vector<string> widgetsToAdd;

	for (auto property : m_mapObject->properties)
	{
		auto name = property->name;
		if (name == "Background")
		{
			background = property->value;
		}
		//if (name == "TextSize");
			//textSize = stoi(property->value);
		if (name == "isVisible")
			if (property->value == "false")
				panel->setVisible(false);

	}

	//auto bg = make_shared<tgui::Picture>("background.jpg");
	//panel->add(bg);
	//bg->moveToBack();
	Color color;
	if (background == "LightGray") color = Color(160, 160, 160);
	else if (background == "Green") color = Color::Green;
	else if (background == "Red") color = Color::Red;
	else if (background == "Blue") color = Color::Blue;
	else if (background == "Yellow") color = Color::Yellow;
	else color = Color(128, 128, 128);

	panel->getRenderer()->setBackgroundColor(color);

	m_guiRenderComponent->addWidgetComponent(this);
	m_mapObject = nullptr;

}
