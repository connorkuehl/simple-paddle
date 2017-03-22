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
 * Ball.h
 */

#ifndef SIMPLEPADDLE_BALL_H_
#define SIMPLEPADDLE_BALL_H_

#include "GameObject.h"
#include "Paddle.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>




// Used to scale the severity of the reflection angle
const auto MAX_BALL_ANGLE = 50.0f;

class Ball : public GameObject {
public:
	Ball(float x, float y, float width, float height, float speed);

	// Returns the Ball to its starting position
	void reset();
	// Checks if Ball is colliding against something, respond if it is
	bool checkCollision(const sf::FloatRect &collidable);
	// Update the Ball logic (moving, colliding, etc)
	void update(float delta);
	// Enable passing Ball object to a RenderWindow draw()
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	// 2D graphic of the Ball
	sf::RectangleShape ball_;
	bool moving_;
	float xdir_;
	float ydir_;
	bool colliding_;
};

#endif

