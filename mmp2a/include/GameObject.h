#pragma region include

#pragma once
#include "stdafx.h"

// stuff
#include "Transformation.h"

// interface
#include "IGameComponent.h"

// enums
#include "GameObjects.h"

#pragma endregion

class GameObject : sf::Transform
{
public:
	GameObject(const GameObjects id);
	GameObject(const GameObjects id, const Transformation transform);

	void update(const float deltaTimeSeconds);

	void exit();

	void moveObject(const sf::Vector2f move);
	void setPosition(const sf::Vector2f& pos);
	void scaleObject(const sf::Vector2f scale); // TODO Refactoring
	void scaleObject(const float scale);
	void rotateObject(const float angle);

	void initTmxData();

	void addComponent(IGameComponent* c);
	void addComponents(vector<IGameComponent*> cv);
	void removeComponent(IGameComponent* c);
	void removeComponents(const GameComponents cId);
	void clearComponents();
	vector<IGameComponent*> findComponents(const GameComponents cId);
	vector<IGameComponent*>::iterator findFirstComponentIterator(const GameComponents cId);
	vector<IGameComponent*>::iterator findFirstComponentIterator(IGameComponent* c);

	//Get-Methods
	GameObjects getId() { return m_id; };

	Transformation & getOriginalTf() { return m_originalTransformation; };
	Transformation & getCurrentTf() { return m_currentTransformation; };

	sf::Vector2f getVelocity() { return m_velocity; };

	//Set-Methods
	void setVelocity(sf::Vector2f v) { m_velocity = v; };

	void setOriginalTf(Transformation tf) { m_originalTransformation = tf; };
	void setCurrentTf(Transformation tf) { m_currentTransformation = tf; };

private:
	std::vector<IGameComponent *> m_components;

	GameObjects m_id;

	sf::Vector2f m_velocity = sf::Vector2f(0.0f, 0.0f);

	Transformation m_originalTransformation;
	Transformation m_currentTransformation;
};