#pragma once
#include "stdafx.h"


struct Transformation {
public:
	Transformation()
		: m_translation(sf::Vector2f(0.0f, 0.0f))
		, m_scaling(sf::Vector2f(1.0f, 1.0f))
		, m_rotation(0.0f)
	{
	}
	Transformation(sf::Vector2f translation, sf::Vector2f scaling, float rotation)
		: m_translation(translation)
		, m_scaling(scaling)
		, m_rotation(rotation)
	{
	}

	sf::Vector2f getTranslation() {
		return m_translation;
	}

	sf::Vector2f getScaling() {
		return m_scaling;
	}

	float getRotation() {
		return m_rotation;
	}

	void moveTf(const sf::Vector2f distance) {
		m_translation += distance;
	}

	void setPosition(const sf::Vector2f pos) {
		m_translation = pos;
	}

	void scaleTf(const sf::Vector2f scaleFactor) {
		m_scaling.x *= scaleFactor.x;
		m_scaling.y *= scaleFactor.y;
	}

	void scaleTf(const float scaleFactor) {
		m_scaling *= scaleFactor;
	}

	void rotateTf(const float angle) {
		m_rotation += angle;
	}

	bool operator==(Transformation & rhs) {
		return m_translation == rhs.getTranslation()
			&& m_scaling == rhs.getScaling()
			&& m_rotation == rhs.getRotation();
	}

	bool operator!=(Transformation & rhs) {
		return !(*this == rhs);
	}



private:
	sf::Vector2f m_translation;
	sf::Vector2f m_scaling;
	float m_rotation;
};