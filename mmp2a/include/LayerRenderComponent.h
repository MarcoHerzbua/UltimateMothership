#pragma region include

#pragma once

#include "stdafx.h"

#include "RenderComponent.h"

#include "GameComponents.h"
#include "LayerComponents.h"

#include "NLTmxMap.h"

using namespace std;
using namespace sf;

#pragma endregion

class LayerRenderComponent : public RenderComponent
{
public:
	LayerRenderComponent(GameObject* gameObject);
	LayerRenderComponent(GameObject* gameObject, NLTmxMapLayer& mapLayer);

	void update(const float deltaTime) override;
	void draw(RenderWindow* window) override;
	void exit() override;
	void setScale(const float scale) override;


	void init(NLTmxMap & tilemap, const map<string, Texture *> & textures, const Vector2f & offset);
	void initTmxData() override;

private:
	LayerComponents m_layerId;
	vector<Sprite *> m_sprites;

	NLTmxMapLayer* m_mapLayer;
};