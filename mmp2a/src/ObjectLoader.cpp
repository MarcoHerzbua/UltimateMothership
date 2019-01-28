#include "stdafx.h"
#include "ObjectLoader.h"

#include "GameObject.h"
#include "Transformation.h"
#include "ComponentLoader.h"

vector<GameObject*> ObjectLoader::loadGameObjects(const NLTmxMap& tilemap)
{
	vector<GameObject*> gameObjects;

	for (auto group : tilemap.groups)
	{
		GameObjects id = stringToGameObjects(group->name);
		if (id == NULL_OBJECT) err() << "id == NULL_OBJECT when loading " << group->name << "\n";
		GameObject* gameObject = createGameObject(id, *group);
		
		gameObject->addComponents(ComponentLoader::loadComponents(*group, gameObject));

		gameObjects.push_back(gameObject);
	}

	return gameObjects;
}

GameObject* ObjectLoader::createGameObject(const GameObjects id, const NLTmxMapObjectGroup& group)
{
	Transformation tf;
	//go throught MapObjectGroupProperties (holds transformation, scale, rotation of GameObject)
	for (auto property : group.properties)
	{
		auto name = property->name;

		if (name == "Angle")
			tf.rotateTf(stof(property->value));

		if (name == "Scale")
			tf.scaleTf(stof(property->value));

		if (name == "TranslationX")
			tf.moveTf(Vector2f(stof(property->value), 0.f));
		if (name == "TranslationY")
			tf.moveTf(Vector2f(0.f, stof(property->value)));
	}

	return new GameObject(id, tf);
}
