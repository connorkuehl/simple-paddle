/*
 * author: Connor Kuehl
 * 
 * `GameObject` is an Abstract Base Class that represents
 * either a Paddle or the Ball. This class bundles the
 * similar behaviors and states that a Paddle and a Ball
 * have (such as moving, x/y position, speed).
 *
 * This file is a part of SimplePaddle, a small side project used
 * to begin learning about SFML.
 *
 * GameObject.cpp
 */

#include "GameObject.h"




GameObject::GameObject(float x, float y, float width, float height, float speed)
: x_{x}, y_{y}, width_{width}, height_{height}, speed_{speed}, start_pos_{x_, y_}
{
}


GameObject::~GameObject()
{
}

/*
 * @return: the x, y coordinates of the GameObject.
 */
sf::Vector2f GameObject::getPosition()
{
	//return sf::Vector2f(x_, y_);
        return {x_, y_};
}

/*
 * Moves the GameObject based on the given direction.
 * -1 = left or down
 *  1 = right or up
 *
 * @param `x_dir`: The horizontal direction to move.
 * @param `y_dir`: The vertical direction to move.
 * @param `delta`: The delta time of the iteration.
 */
void GameObject::move(float x_dir, float y_dir, float delta)
{
	x_ += (x_dir * speed_) * delta;
	y_ += (y_dir * speed_) * delta;
}

/*
 * Returns the GameObject to the position it was created with.
 */
void GameObject::reset()
{
	x_ = start_pos_.x;
	y_ = start_pos_.y;
}
