#include "stdafx.h"
#include "ComponentLoader.h"

#include "IGameComponent.h"
#include "GameObject.h"
#include "NLTmxMap.h"

#include "SpriteRenderComponent.h"
#include "SpriteSwitcherComponent.h"
#include "ShapeRenderComponent.h"
#include "CameraComponent.h"
#include "DebugGeometryRenderComponent.h"
#include "GUIRenderComponent.h"
#include "SteeringComponent.h"
#include "CursorComponent.h"
#include "GUIButtonComponent.h"
#include "MotherShipComponent.h"
#include "FighterShipComponent.h"
#include "FarmShipComponent.h"
#include "GUISteeringComponent.h"
#include "GUILabelComponent.h"
#include "GUIPanelComponent.h"

#include "GameComponents.h"

vector<IGameComponent*> ComponentLoader::loadComponents(const NLTmxMapObjectGroup& group, GameObject* gameObject)
{
	vector<IGameComponent*> components;

	// go over all objects per layer
	for (auto mapObj : group.objects)
	{
		GameComponents id = stringToGameComponents(mapObj->type);
		IGameComponent* component = createComponent(id, *mapObj, gameObject);
		
		components.push_back(component);
	}

	return components;
}

IGameComponent* ComponentLoader::createComponent(const GameComponents id, NLTmxMapObject& mapObject, GameObject* gameObject)
{
	switch (id)
	{
	case SPRITE_RENDER_COMPONENT:			return new SpriteRenderComponent(gameObject, mapObject);
	case SPRITE_SWITCHER_COMPONENT:			return new SpriteSwitcherComponent(gameObject, mapObject);
	case SHAPE_RENDER_COMPONENT:			return new ShapeRenderComponent(gameObject, mapObject);
	case CAMERA_COMPONENT:					return new CameraComponent(gameObject, mapObject);
	case DEBUG_GEOMETRY_RENDER_COMPONENT:	return new DebugGeometryRenderComponent(gameObject, mapObject);
	case STEERING_COMPONENT:				return new SteeringComponent(gameObject, mapObject);
	case CURSOR_COMPONENT:					return new CursorComponent(gameObject, mapObject);
	case GUI_RENDER_COMPONENT:				return new GUIRenderComponent(gameObject, mapObject);
	case GUI_BUTTON_COMPONENT:				return new GUIButtonComponent(gameObject, mapObject);
	case MOTHER_SHIP_COMPONENT:				return new MotherShipComponent(gameObject, mapObject);
	case FIGHTER_SHIP_COMPONENT:			return new FighterShipComponent(gameObject, mapObject);
	case FARM_SHIP_COMPONENT:				return new FarmShipComponent(gameObject, mapObject);
	case GUI_STEERING_COMPONENT:			return new GUISteeringComponent(gameObject, mapObject);
	case GUI_LABEL_COMPONENT:				return new GUILabelComponent(gameObject, mapObject);
	case GUI_PANEL_COMPONENT:				return new GUIPanelComponent(gameObject, mapObject);
	default: break;
	}

	return nullptr;
}
