#pragma once
#include "stdafx.h"

#include "IGameComponent.h"

class SpriteRenderComponent;

using namespace sf;
using namespace std;

class SpriteSwitcherComponent : public IGameComponent
{
public:
	SpriteSwitcherComponent(GameObject* gameObject);
	SpriteSwitcherComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	void update(const float deltaTime) override;
	void exit() override;

	void initTmxData() override;

	void activateSet(int sId);
	void registerSprite(int sId, SpriteRenderComponent* sprite);

private:
	map<int, vector<SpriteRenderComponent*>> m_sets;
	int m_activeSet;

};