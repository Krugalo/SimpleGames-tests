#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
	int keyonoff(1);
	const int w(800);
	const int h(600);
	const float radius(50);



	int keyleft(0), keyright(0), keyup(0), keydown(0), shot(0);


	sf::RenderWindow window(sf::VideoMode(w, h), "Nasze okno");

	sf::Vector2f speed(5, 5);

	sf::Vector2f scale(5, 5);

	//tekstury
	sf::Texture txt; //deklarujemy nazwe zmiennej odpowiedzialnej za grafike
	txt.loadFromFile("characters.gif"); //ladujemy plik z grafika
	const int sprwidth(23);
	sf::IntRect rect(198,452,sprwidth,26); //pierwsza klatka, wycinamy z grafiki
	sf::IntRect lect(11, 452, sprwidth, 26);
	sf::IntRect upect(1, 1, 1, 1);
	sf::IntRect dect(1, 1, 1, 1);

	//bohater
	sf::Sprite bohater(txt, rect);
	bohater.scale(scale);
	bohater.setOrigin(sprwidth/2, 26/2);
	bohater.setPosition(w / 2, h / 2);

	//tekst
	sf::Font ttf;
	ttf.loadFromFile("fonts/OpenSans-Bold.ttf");
	string s("TEST");
	sf::Text text(s, ttf);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setPosition(w / 2, 10);

	//pocisk
	sf::RectangleShape bullet(sf::Vector2f(20, 10));
	bullet.setFillColor(sf::Color::Black);
	bullet.setPosition(-10, -10);
	sf::Vector2f Speed2(30, 0);


	sf::Clock zegar;

	window.setFramerateLimit(60); //60 fps

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();


			//stan klawiatury
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) keyleft = 1; else keyleft = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) keyright = 1; else keyright = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) keyup = 1; else keyup = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) keydown = 1; else keydown = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (bullet.getPosition().y < 0) //cd na strzał
				{
					shot = 1;

					bullet.setPosition(bohater.getPosition());
					bullet.setFillColor(sf::Color::White);
					if (keyleft == 1)
						bullet.move(-30, 0);
					else if(keyright == 1)
						bullet.move(Speed2);
				}

			}

		}
		sf::Vector2f pos1 = bohater.getPosition();
		sf::Vector2f pos2 = bullet.getPosition();

		//kontrolki + animacja
		if (keyleft == 1)
		{
			bohater.move(speed.x * (-1), 0);
			if (zegar.getElapsedTime().asSeconds() > 0.1)
			{
				if (lect.left > 11 + 6 * sprwidth)
					lect.left -= sprwidth * 7;
				else
					lect.left += sprwidth;

				bohater.setTextureRect(lect);
				zegar.restart();
			}
		}
		if (keyright == 1) 
		{
			bohater.move(speed.x, 0);
			if (zegar.getElapsedTime().asSeconds() > 0.1)
			{
				if (rect.left > 198 + 6 * sprwidth)
					rect.left -= sprwidth * 7;
				else
					rect.left += sprwidth;

				bohater.setTextureRect(rect);
				zegar.restart();
			}
		}
		if (keyup == 1)
		{
			bohater.move(0, speed.y * (-1));
		}
		if (keydown == 1)
		{
			bohater.move(0, speed.y);
		}

		//strzał
		if (shot == 1) bullet.move(Speed2);
		if (pos2.x > window.getSize().x || pos2.x < 0)
		{
			bullet.move(0, 0);
			bullet.setPosition(-10, -10);
			bullet.setFillColor(sf::Color::Black);
			shot == 0;
		}



		//kolizja ze ściankami
		if (pos1.x - bohater.getOrigin().x > window.getSize().x)
			bohater.setPosition(window.getSize().x - bohater.getOrigin().x*2, pos1.y);
		if (pos1.x - bohater.getOrigin().x < 0)
			bohater.setPosition(bohater.getOrigin().x*2, pos1.y);
		if (pos1.y + bohater.getOrigin().y > window.getSize().y)
			bohater.setPosition(pos1.x, window.getSize().y - bohater.getOrigin().y*2);
		if (pos1.y - bohater.getOrigin().y < 0)
			bohater.setPosition(pos1.x, bohater.getOrigin().y*2);


		
		window.clear(sf::Color(72,160,73,255));

		window.draw(bohater);
		window.draw(text);
		window.draw(bullet);

		window.display();

	}

	return 0;
}