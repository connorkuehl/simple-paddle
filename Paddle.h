/*
 * author: Connor Kuehl
 * 
 * `Paddle` is a class that represents a player's paddle in
 * the game of SimplePaddle. The player can move their paddle up or
 * down in an attempt to protect their end of the field and
 * to direct the ball towards the opposing player's side.
 *
 * The player can affect the trajectory of the Ball by hitting
 * it selectively. If the player uses the top part of the paddle
 * to hit the Ball, the Ball will move up. Similarly, if the bottom
 * part of the Paddle is used, the Ball will go downwards. The angle
 * of the Ball's trajectory becomes more severe the farther from 
 * the center of the Paddle the Ball is when it hits the Paddle.
 *
 * This file is a part of SimplePaddle, a small side project used
 * to begin learning about SFML.
 *
 * Paddle.h
 */

#ifndef SIMPLEPADDLE_PADDLE_H_
#define SIMPLEPADDLE_PADDLE_H_

#include "GameObject.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>




class Paddle: public GameObject
{
public:
	Paddle(float x, float y, float width, float height, float speed);

	// Update Paddle logic (input, movement)
	void update(float delta);
	// Enables passing a Paddle into a RenderWindow draw() call
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	// Returns the bounding box for the Paddle
	sf::FloatRect getCollisionBox() const;
	// Allows customizing of up/down controls for 2 player games
	void setKeyBindings(sf::Keyboard::Key up, sf::Keyboard::Key down);

protected:
	// Handle player input
	void interact(float delta);

private:
	// 2D graphic of the Paddle
	sf::RectangleShape paddle_;
	sf::Keyboard::Key up_;
	sf::Keyboard::Key down_;
};

#endif
