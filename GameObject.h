/*
 * author: Connor Kuehl
 * 
 * `GameObject` is an Abstract Base Class that represents
 * either a Paddle or the Ball. This class bundles the
 * similar behaviors and states that a Paddle and a Ball
 * have (such as moving, x/y position, speed).
 *
 * This file is a part of , a small side project used
 * to begin learning about SFML.
 *
 * GameObject.h
 */

#ifndef SIMPLEPADDLE_GAMEOBJECT_H_
#define SIMPLEPADDLE_GAMEOBJECT_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>




class GameObject: public sf::Drawable
{
public:
	GameObject(float x, float y, float width, float height, float speed);
	virtual ~GameObject();

	// Move the GameObject to its starting position
	void reset();
	// Update the GameObject's state
	virtual void update(float delta) = 0;
	// For convenience, can pass GameObject into a Window draw call
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	void move(float x_dir, float y_dir, float delta);
	sf::Vector2f getPosition();

private:
	float x_;
	float y_;
	float width_;
	float height_;
	float speed_;
	sf::Vector2f start_pos_;
};

#endif
