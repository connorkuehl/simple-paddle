/*
 * author: Connor Kuehl
 * 
 * `Ball` is the Ball in SimplePaddle. It's autonomous for the most part.
 * It's responsible for handling its own collision with the various
 * collidable objects in the game (Paddles, game boundaries).
 *
 * This file is a part of SimplePaddle, a small side project used
 * to begin learning about SFML.
 * 
 * Ball.cpp
 */

#include "Ball.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>

#include <iostream>
#include <cmath>




Ball::Ball(float x, float y, float width, float height, float speed)
	: GameObject{x, y, width, height, speed}, ball_{{width, height}},
	  moving_{true}, xdir_{-1}, ydir_{0}, colliding_{false}
{
	// Set visual component's color and location.
	ball_.setFillColor(sf::Color::White);
	ball_.setPosition(x, y);
}

/*
 * Used to update any required logic for the Ball,
 * such as moving it.
 *
 * @param `delta`: The delta time of this iteration.
 */
void Ball::update(float delta)
{
	if (moving_) {
		move(xdir_, ydir_, delta);
		ball_.setPosition(getPosition());
		ball_.setRotation(ball_.getRotation() + ydir_);
	}
}

/*
 * For convenience's sake, allows us to simply pass in the Paddle object
 * to a sf::RenderWindow `draw()` call.
 */
void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(ball_);
}

/*
 * Checks to see if the Ball is colliding with the BoundingBox
 * provided. If it is, the Ball will calculate its trajectory
 * depending on if it struck a Paddle or an upper/bottom bound.
 *
 * @param `collidable`: The BoundingBox to see if it collided with.
 * @return: True if the Ball is colliding with the `collidable`, false
 *          if not.
 */
bool Ball::checkCollision(const sf::FloatRect &collidable)
{
	// TODO: This is a travesty, optimize this function.
	auto ball_coll = ball_.getGlobalBounds();

	if (!ball_coll.intersects(collidable))
		return false;

	if (collidable.width > collidable.height) {
		ydir_ *= -1;
	}
	else { 
		// must be a paddle then
		// adjust trajectory after hit

		// determine the y value of the center of the paddle
		auto center = (collidable.height / 2) + collidable.top;
		// determine the distance of the ball's y-value from the center of the paddle's y-value
		// SFML's y-axis is reversed, so I multiplied it by -1 to convert it to regular
		auto distance = (center - ((ball_coll.height / 2) + ball_coll.top)) * -1;

		ydir_ = sin(distance / MAX_BALL_ANGLE);
		xdir_ *= -1;
	}

	return true;
}

/*
 * Returns the Ball to the position handed to
 * its constructor when it was made.
 */
void Ball::reset()
{
	GameObject::reset();
	xdir_ = 1;
	ydir_ = 0;
}
