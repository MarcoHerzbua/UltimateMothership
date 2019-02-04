#include "stdafx.h"
#include "SpriteSwitcherComponent.h"
#include "SpriteRenderComponent.h"

SpriteSwitcherComponent::SpriteSwitcherComponent(GameObject* gameObject)
	: IGameComponent(gameObject)
{
	m_id = SPRITE_SWITCHER_COMPONENT;
}

SpriteSwitcherComponent::SpriteSwitcherComponent(GameObject* gameObject, NLTmxMapObject& mapObject)
	: IGameComponent(gameObject, mapObject)
{
	m_id = SPRITE_SWITCHER_COMPONENT;
}

void SpriteSwitcherComponent::update(const float deltaTime)
{
}

void SpriteSwitcherComponent::exit()
{
}

void SpriteSwitcherComponent::initTmxData()
{
}

void SpriteSwitcherComponent::activateSet(int sId)
{
	for (auto& set : m_sets)
		for (auto& sprite : set.second)
			sprite->deactivate();

	m_activeSet = 0;
	if (m_sets[sId].size() > 0)
		m_activeSet = sId;

	for (auto sprite : m_sets[m_activeSet])
		sprite->activate();
}

void SpriteSwitcherComponent::registerSprite(int sId, SpriteRenderComponent* sprite)
{
	m_sets[sId].push_back(sprite);
}
