#include "SFML/Graphics.hpp"

#include <ctime>
#include <array>

const int N = 45;
const int M = 30;
const int size = 24;
int width = size * N;
int height = size * M;

int dir;
int num = 4;

class Snake
{
public:
	int x;
	int y;
};

std::array<Snake, 100> snake;

class Fruit
{
public:
	int x;
	int y;
};

Fruit fruit;

void Tick()
{
	for (int i = num; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	switch (dir)
	{
	case 0:	snake.front().y += 1;
		break;
	case 1:	snake.front().x -= 1;
		break;
	case 2:	snake.front().x += 1;
		break;
	case 3:	snake.front().y -= 1;
		break;
	}

	if ((snake.front().x == fruit.x) && (snake.front().y == fruit.y))
	{
		num++;
		fruit.x = rand() % N;
		fruit.y = rand() % M;
	}
	
	// x
	if (snake.front().x > N)
		snake.front().x = 0;
	if (snake.front().x < 0)
		snake.front().x = N;
	// y
	if (snake.front().y > M)
		snake.front().y = 0;
	if (snake.front().y < 0)
		snake.front().y = M;

	for (int i = 1; i < num; i++)
		if (snake.front().x == snake[i].x && snake.front().y == snake[i].y)
			num = i;
}

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game!");

	sf::Texture tex1;
	sf::Texture tex2;
	tex1.loadFromFile("images/white.png");
	tex2.loadFromFile("images/red.png");

	sf::Sprite spr1;
	sf::Sprite spr2;
	spr1.setTexture(tex1);
	spr2.setTexture(tex2);
	spr1.setScale(1.5f, 1.5f);
	spr2.setScale(1.5f, 1.5f);

	sf::Clock clock;
	float timer = 0;
	float delay = 0.1;

	fruit.x = 10;
	fruit.y = 10;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		// Input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		dir = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	dir = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		dir = 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		dir = 0;

		// Timer
		if (timer > delay)
		{
			timer = 0;
			Tick();
		}

		// Draw stuff
		window.clear();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				spr1.setPosition(i * size, j * size);
				window.draw(spr1);
			}
		}

		for (int i = 0; i < num; i++)
		{
			spr2.setPosition(snake.front().x * size, snake.front().y * size);
			window.draw(spr2);
		}

		spr2.setPosition(fruit.x * size, fruit.y * size);
		window.draw(spr2);

		window.display();
	}


	return 0;
}