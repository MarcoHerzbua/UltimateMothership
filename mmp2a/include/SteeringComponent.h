#pragma region include

#pragma once
#include "stdafx.h"

#include "IGameComponent.h"

#include "ControllerComponents.h"

class ControllerComponent;
class Node;

using namespace std;
using namespace sf;

#pragma endregion

class SteeringComponent : public IGameComponent
{
public:
	SteeringComponent(GameObject* gameObject);
	SteeringComponent(GameObject* gameObject, NLTmxMapObject& mapObject);

	virtual void update(const float deltaTimeSeconds) override;
	void exit() override;

	virtual void initTmxData() override;

	void updateUnit(const float deltaTimeSeconds);
	
	void registerController(ControllerComponent* c);
	void removeController(ControllerComponents cId);
	ControllerComponent* findController(ControllerComponents cId);
	vector<ControllerComponent*>::iterator findControllerIterator(const ControllerComponents cId);
	void setActiveController(ControllerComponents cId);
	void setActiveController(ControllerComponent* c);

	void moveToTargetNode(Node* n);
	bool isMoving();

	ControllerComponent* getActiveController() { return m_activeController; };

	virtual void setCurrentNode(Node* node);
	Node* getCurrentNode() { return m_currentNode; }
	
	void setTimeSinceLastInput(float time) { m_timeSinceLastInput = time; }
	void addTimeSinceLastInput(float time) { m_timeSinceLastInput += time; }
	float getTimeSinceLastInput() { return m_timeSinceLastInput; }

	float getTimeDelay() { return m_timeDelay; };

	int getPlayerIndex() { return m_playerIndex; };
	void setPlayerIndex(int idx) { m_playerIndex = idx; };
protected:
	static constexpr float m_timeDelay = 0.14f;
	float m_timeSinceLastInput = 0.0f;

	Node* m_currentNode;

	ControllerComponent* m_activeController;
	vector<ControllerComponent*> m_controller;

	int m_playerIndex;
	bool m_aiControlled;

	bool m_locked = false;
	bool m_doneWithMovement = true;
};