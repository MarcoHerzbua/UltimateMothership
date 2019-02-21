#pragma region include

#pragma once
#include "stdafx.h"

#include "Transformation.h"
#include "GameObjects.h"
#include "GameComponents.h"

class IGameComponent;

using namespace std;
using namespace sf;

#pragma endregion

class GameObject : Transform
{
public:
	GameObject(GameObjects id);
	GameObject(GameObjects id, Transformation transform);

	void update(float deltaTimeSeconds);

	void exit();

	void moveObject(sf::Vector2f move);
	void setPosition(const sf::Vector2f& pos);
	void scaleObject(sf::Vector2f scale); // TODO Refactoring
	void scaleObject(float scale);
	void rotateObject(float angle);

	void initTmxData();

	void addComponent(IGameComponent* c);
	void addComponents(vector<IGameComponent*> cv);
	void removeComponent(IGameComponent* c);
	void removeComponents(GameComponents cId);
	void clearComponents();
	vector<IGameComponent*> findComponents(GameComponents cId);
	vector<IGameComponent*>::iterator findFirstComponentIterator(GameComponents cId);
	vector<IGameComponent*>::iterator findFirstComponentIterator(IGameComponent* c);

	//Get-Methods
	GameObjects getId() { return m_id; };

	Transformation& getOriginalTf() { return m_originalTransformation; };
	Transformation& getCurrentTf() { return m_currentTransformation; };

	sf::Vector2f getVelocity() { return m_velocity; };

	//Set-Methods
	void setVelocity(sf::Vector2f v) { m_velocity = v; };

	void setOriginalTf(Transformation tf) { m_originalTransformation = tf; };
	void setCurrentTf(Transformation tf) { m_currentTransformation = tf; };

private:
	vector<IGameComponent *> m_components;

	GameObjects m_id;

	sf::Vector2f m_velocity = sf::Vector2f(0.0f, 0.0f);

	Transformation m_originalTransformation;
	Transformation m_currentTransformation;
};