#include "stdafx.h"
#include "ComponentLoader.h"

#include "GameObjectManager.h"
#include "InputManager.h"

#include "IGameComponent.h"
#include "SpriteRenderComponent.h"
#include "ShapeRenderComponent.h"
#include "CameraComponent.h"
#include "RigidBodyComponent.h"
#include "CollisionComponent.h"
#include "DebugGeometryRenderComponent.h"
#include "PointCounterComponent.h"
#include "DeathZoneComponent.h"
#include "GUIRenderComponent.h"
#include "SteeringComponent.h"
#include "GUIButtonComponent.h"
#include "MotherShipComponent.h"
#include "FighterShipComponent.h"
#include "FarmShipComponent.h"

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

		//add a debugComponent to visualize BoundingBox
		if (id == GameComponents::COLLISION_COMPONENT)
		{
			IGameComponent * debugComp = createComponent(DEBUG_GEOMETRY_RENDER_COMPONENT, *mapObj, gameObject);
			gameObject->addComponent(debugComp);
		}
	}

	return components;
}

IGameComponent* ComponentLoader::createComponent(const GameComponents id, NLTmxMapObject& mapObject, GameObject* gameObject)
{
	switch (id)
	{
	case SPRITE_RENDER_COMPONENT:			return new SpriteRenderComponent(gameObject, mapObject);
	case SHAPE_RENDER_COMPONENT:			return new ShapeRenderComponent(gameObject, mapObject);
	case CAMERA_COMPONENT:					return new CameraComponent(gameObject, mapObject);
	case RIGID_BODY_COMPONENT:				return new RigidBodyComponent(gameObject, mapObject);
	case COLLISION_COMPONENT:				return new CollisionComponent(gameObject, mapObject);
	case DEBUG_GEOMETRY_RENDER_COMPONENT:	return new DebugGeometryRenderComponent(gameObject, mapObject);
	case POINT_COUNTER_COMPONENT:			return new PointCounterComponent(gameObject, mapObject);
	case DEATH_ZONE_COMPONENT:				return new DeathZoneComponent(gameObject, mapObject);
	case STEERING_COMPONENT:				return new SteeringComponent(gameObject, mapObject);
	case GUI_RENDER_COMPONENT:				return new GUIRenderComponent(gameObject, mapObject);
	case GUI_BUTTON_COMPONENT:				return new GUIButtonComponent(gameObject, mapObject);
	case MOTHER_SHIP_COMPONENT:				return new MotherShipComponent(gameObject, mapObject);
	case FIGHTER_SHIP_COMPONENT:			return new FighterShipComponent(gameObject, mapObject);
	case FARM_SHIP_COMPONENT:				return new FarmShipComponent(gameObject, mapObject);
	default: break;
	}

	return nullptr;
}
