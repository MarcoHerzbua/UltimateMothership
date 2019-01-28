#pragma region include

#include "stdafx.h"
#include "RenderComponent.h"

// game classes 
#include "Game.h"
#include "GameObject.h"

// manager
#include "RenderManager.h"

#pragma endregion

RenderComponent::RenderComponent(GameObject * gameObject)
	: IGameComponent(gameObject)
{
	RenderManager::getInstance().addComponent(this);
}

RenderComponent::RenderComponent(GameObject * gameObject, NLTmxMapObject & mapObject)
	: IGameComponent(gameObject, mapObject)
{
	RenderManager::getInstance().addComponent(this);
}