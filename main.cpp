/*
 * author: Connor Kuehl
 * 
 * The entry point for the game. This source file
 * is basically just the Game loop. It also defines
 * parameters for the size of the game objects, etc.
 * 
 * main.cpp
 */

#include "Paddle.h"
#include "Ball.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window/Keyboard.hpp"




// sizes of things
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float PADDLE_WIDTH = 25.f;
const float PADDLE_HEIGHT = 100.f;
const float PADDLE_SPEED = 250.f;
const float PADDLE_OFFSET = 35.f;
const float BALL_RADIUS = 20.f;
const float BALL_SPEED = 350.f;
const std::string GAME_NAME = "Simple Paddle";

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_NAME);
	window.setFramerateLimit(60);

	// set up the score font stuff
	sf::Font font;
	font.loadFromFile("res/imagine_font.ttf");
	// player 1 score text
	sf::Text p1_score_text;
	p1_score_text.setPosition(sf::Vector2f((SCREEN_WIDTH / 3), 25.f));
	p1_score_text.setScale(2.f, 2.f);
	p1_score_text.setFont(font);
	// player 2 score text
	sf::Text p2_score_text;
	p2_score_text.setPosition(sf::Vector2f((SCREEN_WIDTH / 3) * 1.75, 25.f));
	p2_score_text.setScale(2.f, 2.f);
	p2_score_text.setFont(font);

	// set up ball and paddles
	Ball ball(
		(SCREEN_WIDTH / 2) - BALL_RADIUS,
		(SCREEN_HEIGHT / 2) - BALL_RADIUS,
		BALL_RADIUS,
		BALL_RADIUS,
		BALL_SPEED
	);

	Paddle player1(
		PADDLE_OFFSET, 
		(SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2), 
		PADDLE_WIDTH, 
		PADDLE_HEIGHT, 
		PADDLE_SPEED
	);

	Paddle player2(
		(SCREEN_WIDTH - PADDLE_OFFSET) - PADDLE_WIDTH,
		(SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2),
		PADDLE_WIDTH,
		PADDLE_HEIGHT,
		PADDLE_SPEED
	);

	player1.setKeyBindings(sf::Keyboard::Key::Q, sf::Keyboard::Key::A);

	// scores
	int p1_score = 0;
	int p2_score = 0;
	bool scored = false;

	// score-zones -- if the ball crosses into these the opposing player gets a point
	sf::FloatRect p1_zone(sf::Vector2f(0.f, 0.f), sf::Vector2f(PADDLE_OFFSET, SCREEN_HEIGHT));
	sf::FloatRect p2_zone(sf::Vector2f(SCREEN_WIDTH - PADDLE_OFFSET, 0.f), sf::Vector2f(PADDLE_OFFSET, SCREEN_HEIGHT));

	// vertical bounds
	sf::RectangleShape top_bound(sf::Vector2f(SCREEN_WIDTH, 10.f));
	top_bound.setPosition(0, 0);
	top_bound.setFillColor(sf::Color::White);
	sf::RectangleShape bot_bound(sf::Vector2f(SCREEN_WIDTH, 10.f));
	bot_bound.setPosition(0, SCREEN_HEIGHT - 10.f);
	bot_bound.setFillColor(sf::Color::White);

	sf::Clock clock;
	// game loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float delta = clock.restart().asSeconds();

		// process score point and reset game!
		if (scored) {
			player1.reset();
			player2.reset();
			ball.reset();
			scored = false;
		}

		// update objects
		ball.update(delta);
		player1.update(delta);
		player2.update(delta);
		p1_score_text.setString(std::to_string(p1_score));
		p2_score_text.setString(std::to_string(p2_score));

		// collision checking
		ball.checkCollision(player1.getCollisionBox());
		ball.checkCollision(player2.getCollisionBox());
		ball.checkCollision(top_bound.getGlobalBounds());
		ball.checkCollision(bot_bound.getGlobalBounds());
		if (ball.checkCollision(p1_zone)) {
			++p2_score;
			scored = true;
		}

		if (ball.checkCollision(p2_zone)) {
			++p1_score;
			scored = true;
		}

		// draw
		window.clear();
		window.draw(ball);
		window.draw(player1);
		window.draw(player2);
		window.draw(p1_score_text);
		window.draw(p2_score_text);
		window.draw(top_bound);
		window.draw(bot_bound);
		window.display();
	}



	return 0;
}