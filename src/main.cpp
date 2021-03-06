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

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <vector>



// sizes of things
const auto SCREEN_WIDTH = 640;
const auto SCREEN_HEIGHT = 480;
const auto PADDLE_WIDTH = 25.f;
const auto PADDLE_HEIGHT = 100.f;
const auto PADDLE_SPEED = 250.f;
const auto PADDLE_OFFSET = 35.f;
const auto BALL_RADIUS = 20.f;
const auto BALL_SPEED = 350.f;
const std::string GAME_NAME{"Simple Paddle"};

int main(int argc, char* argv[])
{
	sf::RenderWindow window({SCREEN_WIDTH, SCREEN_HEIGHT}, GAME_NAME);
	window.setFramerateLimit(60);

	// set up the score font stuff
	sf::Font font;
	font.loadFromFile("res/imagine_font.ttf");
	// player 1 score text
	sf::Text p1_score_text;
	p1_score_text.setPosition({SCREEN_WIDTH / 3, 25.f});
	p1_score_text.setCharacterSize(72);
	p1_score_text.setFont(font);
	p1_score_text.setString(std::to_string(0));
	// player 2 score text
	sf::Text p2_score_text;
	p2_score_text.setPosition({(SCREEN_WIDTH / 3) * 1.75, 25.f});
	p2_score_text.setCharacterSize(72);
	p2_score_text.setFont(font);
	p2_score_text.setString(std::to_string(0));

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

	// For drawing the "net" in the center of the game board
	std::vector<sf::RectangleShape> net;
	for (int i = 0; i < SCREEN_HEIGHT; i += 32) {
		sf::RectangleShape net_block({16, 16});
		net_block.setPosition((SCREEN_WIDTH / 2) - 8, i);
		net_block.setFillColor(sf::Color::White);
		net.push_back(net_block);
	}

	player1.setKeyBindings(sf::Keyboard::Key::Q, sf::Keyboard::Key::A);

	// scores
	auto p1_score = 0;
	auto p2_score = 0;
	auto scored   = false;

	// score-zones -- if the ball crosses into these the opposing player gets a point
	sf::FloatRect p1_zone({0.f, 0.f}, {PADDLE_OFFSET, SCREEN_HEIGHT});
	sf::FloatRect p2_zone({SCREEN_WIDTH - PADDLE_OFFSET, 0.f}, {PADDLE_OFFSET, SCREEN_HEIGHT});

	// vertical bounds
	sf::RectangleShape top_bound({SCREEN_WIDTH, 10.f});
	top_bound.setPosition(0, 0);
	top_bound.setFillColor(sf::Color::White);
	sf::RectangleShape bot_bound({SCREEN_WIDTH, 10.f});
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

		// process score point and reset positions!
		if (scored) {
			scored = false;
			player1.reset();
			player2.reset();
			ball.reset();
			p1_score_text.setString(std::to_string(p1_score));
			p2_score_text.setString(std::to_string(p2_score));
		}

		// update objects
		ball.update(delta);
		player1.update(delta);
		player2.update(delta);

		// collision checking
		ball.checkCollision(player1.getCollisionBox());
		ball.checkCollision(player2.getCollisionBox());
		ball.checkCollision(top_bound.getGlobalBounds());
		ball.checkCollision(bot_bound.getGlobalBounds());

		// check to see if the ball went into a score zone
		if (ball.checkCollision(p1_zone)) {
			++p2_score;
			scored = true;
		}

		if (ball.checkCollision(p2_zone)) {
			++p1_score;
			scored = true;
		}

		// draw objects!
		window.clear(sf::Color::Black);
		window.draw(ball);
		window.draw(player1);
		window.draw(player2);
		window.draw(p1_score_text);
		window.draw(p2_score_text);
		window.draw(top_bound);
		window.draw(bot_bound);
		for (auto& block : net)
			window.draw(block);
		window.display();
	}



	return 0;
}