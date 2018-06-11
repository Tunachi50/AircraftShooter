#include "SFML/Graphics.hpp"


class Game
{
public:
		 Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	sf::RenderWindow mWindow;
	sf::CircleShape mPlayer;
	bool isMovingUp = false;
	bool isMovingDown = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
};

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "Aircraft shooter")
	, mPlayer()
{
	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed :
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased :
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);

	if (isMovingUp)
		movement.y -= 1.f;
	if (isMovingDown)
		movement.y += 1.f;
	if (isMovingLeft)
		movement.x -= 1.f;
	if (isMovingRight)
		movement.x += 1.f;

	mPlayer.move(movement * deltaTime.asSeconds() * 200.f);
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		isMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		isMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		isMovingRight = isPressed;
}




int main()
{
	Game game;

	game.run();
}