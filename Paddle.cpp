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
 * Paddle.cpp
 */

#include "Paddle.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>




Paddle::Paddle(float x, float y, float width, float height, float speed)
	: GameObject(x, y, width, height, speed), paddle_(sf::Vector2f(width, height)),
	  up_(sf::Keyboard::Key::Up), down_(sf::Keyboard::Key::Down)
{
	// set the visual component's color and position
	paddle_.setFillColor(sf::Color::White);
	paddle_.setPosition(sf::Vector2f(x, y));
}

/*
 * Used to update any required logic for the Paddle,
 * such as input.
 *
 * @param `delta`: The delta time of this iteration.
 */
void Paddle::update(float delta)
{
	// handle player input
	interact(delta);
}

/*
 * Checks the Paddle's registered keybindings to see
 * if they're being acted upon. If they are, move the
 * Paddle appropriately.
 *
 * @param `delta`: The delta time of this iteration.
 */
void Paddle::interact(float delta)
{
	if (sf::Keyboard::isKeyPressed(up_))
		move(0, -1, delta);
	else if (sf::Keyboard::isKeyPressed(down_))
		move(0, 1, delta);
	paddle_.setPosition(getPosition());
}

/*
 * For convenience's sake, allows us to simply pass in the Paddle object
 * to a sf::RenderWindow `draw()` call.
 */
void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(paddle_);
}

/*
 * @return: The bounding box of the Paddle.
 */
sf::FloatRect Paddle::getCollisionBox() const
{
	return paddle_.getGlobalBounds();
}

/*
 * Sets the up and down controls for the Paddle. Used in `interact()`.
 * 
 * @param `up`: The sf::Keyboard::Key to check to move the Paddle up.
 * @param `down`: The sf::Keyboard::Key to check to move the Paddle down
 */
void Paddle::setKeyBindings(sf::Keyboard::Key up, sf::Keyboard::Key down)
{
	up_ = up;
	down_ = down;
}
