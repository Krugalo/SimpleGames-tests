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

	float gravity(1); //grawitacja



	int keyleft(0), keyright(0), keyup(0), keydown(0), shot(0);


	sf::RenderWindow window(sf::VideoMode(w, h), "Zelda");

	sf::Vector2f speed(5, 5);

	sf::Vector2f scale(5, 5);

	//tekstury
	sf::Texture txt; //deklarujemy nazwe zmiennej odpowiedzialnej za grafike
	txt.loadFromFile("characters.gif"); //ladujemy plik z grafika
	const int sprwidth(23);
	sf::IntRect rect(198, 452, sprwidth, 26); //pierwsza klatka, wycinamy z grafiki
	sf::IntRect lect(11, 452, sprwidth, 26);
	sf::IntRect upect(1, 1, 1, 1);
	sf::IntRect dect(1, 1, 1, 1);

	//bohater
	sf::Sprite bohater(txt, rect);
	bohater.scale(scale);
	bohater.setOrigin(sprwidth / 2, 26 / 2);
	bohater.setPosition(w / 2, h / 2);

	//tekst
	sf::Font ttf;
	ttf.loadFromFile("fonts/OpenSans-Bold.ttf");
	string s("TEST");
	sf::Text text(s, ttf);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setPosition(w / 2, 10);

	//Platforma 1
	sf::RectangleShape square(sf::Vector2f(100, 10));
	square.setFillColor(sf::Color::Black);
	square.setOrigin(25, 5);
	square.setPosition(25, 400);
	sf::Vector2f DirectSpeed3(2, 2);


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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) keyup = 1; 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) keydown = 1; else keydown = 0;


		}

		sf::Vector2f pos1 = bohater.getPosition();
		sf::Vector2f pos2 = square.getPosition();

		sf::FloatRect heroBox = bohater.getGlobalBounds();
		sf::FloatRect squareBox = square.getGlobalBounds();

		bohater.move(0, speed.y);

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
			if (heroBox.intersects(squareBox))
			{
				speed.y = 0;
				bohater.move(0, -20);
				
				
			}
			if (speed.y > 0)
				keyup = 0;
		}
		/*if (keydown == 1)
		{
			bohater.move(0, speed.y);
		}*/

		
		//kolizja ze ściankami
		if (pos1.x - bohater.getOrigin().x > window.getSize().x) // prawa
			bohater.setPosition(window.getSize().x - bohater.getOrigin().x * 2, pos1.y);
		if (pos1.x - bohater.getOrigin().x < 0) // lewa
			bohater.setPosition(bohater.getOrigin().x * 2, pos1.y);
		if (pos1.y - bohater.getOrigin().y > window.getSize().y) // dol
			bohater.setPosition(sprwidth / 2, 26 / 2);
		if (pos1.y - bohater.getOrigin().y < 0) // gora
			bohater.setPosition(pos1.x, bohater.getOrigin().y * 2);

		if (heroBox.intersects(squareBox))
		{
			speed.y = 0;
			//bohater.setPosition(bohater.getPosition().x, square.getPosition().y - heroBox.height / 2);
		}

		//grawitacja
		if (speed.y >= 0 && heroBox.intersects(squareBox) == false)
		{
			if (zegar.getElapsedTime().asSeconds() > 0.1)
			{
				speed.y = speed.y + gravity;
				zegar.restart();
			}
		}
		else if (heroBox.intersects(squareBox) == false)
		{
			if (zegar.getElapsedTime().asSeconds() > 0.1)
			{
				speed.y = speed.y + gravity;
				zegar.restart();
			}
		}
		/*if (pos1.y > window.getSize().y)
		{
			speed.y = 0;
			speed.x = 0;
			
		}*/


		window.clear(sf::Color(72, 160, 73, 255));

		window.draw(bohater);
		window.draw(text);
		window.draw(square);
		

		window.display();

	}

	return 0;
}