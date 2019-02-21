#pragma region include

#include "stdafx.h"
#include "RenderComponent.h"

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


void RenderComponent::exit()
{
	RenderManager::getInstance().removeComponent(this);
}

