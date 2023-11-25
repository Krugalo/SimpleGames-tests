#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

int keyleft(0), keyright(0), keyup(0), keydown(0), shot(0), shot2(0), score(0), lives(3);

void zdarzeniasfml(sf::RenderWindow& okno, sf::CircleShape& a, sf::RectangleShape& b, sf::Vector2f& s2, sf::RectangleShape& b2)
{
	sf::Event event;



	while (okno.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			okno.close();


		//stan klawiatury
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) keyleft = 1; else keyleft = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) keyright = 1; else keyright = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) keyup = 1; else keyup = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) keydown = 1; else keydown = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (b.getPosition().y < 0) //cd na strzał
			{
				shot = 1;
				
				b.setFillColor(sf::Color::White);
				if (shot2 == 0)
					b.setPosition(a.getPosition());
				else if (shot2 == 1 && shot == 1)
				{
					b.setPosition(a.getPosition().x, a.getPosition().y + 20);
					b2.setPosition(a.getPosition().x, a.getPosition().y - 20);
					b2.setFillColor(sf::Color::White);
				}
			}
		}

	}
}

void ruchbohatera(sf::CircleShape& a, sf::RectangleShape& b, sf::RenderWindow& okno, sf::Vector2f& s1, sf::Vector2f& s2, sf::Vector2f& pos2, sf::Vector2f& pos3, sf::RectangleShape &b2, sf::Text &text, stringstream &s)
{
	//kontrolki
	//if (keyleft == 1) shape.move(Speed1.x * (-1), 0);
	//if (keyright == 1) shape.move(Speed1.x, 0);
	if (keyup == 1) a.move(0, s1.y * (-1));
	if (keydown == 1) a.move(0, s1.y);
	//strzał
	if (shot == 1) b.move(s2); //ruch
	if (shot == 1 && shot2 == 1) b2.move(s2);
	if (pos2.x > okno.getSize().x) //powrot pocisku 1
	{
		b.move(0, 0);
		b.setPosition(-10, -10);
		b.setFillColor(sf::Color::Black);
		shot = 0;
		score++;
		s << "SCORE: " << score;
		sf::Font ttf;
		sf::Text text(s.str().c_str(), ttf); 
		text.setCharacterSize(25);
		text.setFillColor(sf::Color::Black);
		text.setPosition(10, 10);
	}

	if (pos3.x > okno.getSize().x) //powrot pocisku 2
	{
		b2.move(0, 0);
		b2.setPosition(-10, -10);
		b2.setFillColor(sf::Color::Black);
		shot = 0;
	}
	if (score >= 2)
	{
		shot2 = 1;
	}
}

void kolizje(sf::Vector2f& pos1, const float& radius, sf::RenderWindow& window, sf::CircleShape& shape, sf::CircleShape &w1, sf::RectangleShape &bullet, sf::RectangleShape &bullet2)
{
	//kolizja ze ściankami
	if (pos1.x + radius > window.getSize().x)//prawo
		shape.setPosition(window.getSize().x - radius, pos1.y);
	if (pos1.x < radius)//lewo
		shape.setPosition(radius, pos1.y);
	if (pos1.y + radius > window.getSize().y)//dol
		shape.setPosition(pos1.x, window.getSize().y - radius);
	if (pos1.y < radius + 100)//gora
		shape.setPosition(pos1.x, radius + 100);

	//pocisk i wrog
	if (bullet.getGlobalBounds().intersects(w1.getGlobalBounds()))
	{
		score++;
		w1.setPosition(1200 + radius * 2, 300);
		bullet.setPosition(-10, -10);
		bullet.setFillColor(sf::Color::Black);
	}
	if (bullet2.getGlobalBounds().intersects(w1.getGlobalBounds()))
	{
		score++;
		w1.setPosition(1200 + radius * 2, 300);
		bullet2.setPosition(-10, -10);
		bullet2.setFillColor(sf::Color::Black);
	}
	

	//bohater i wrog
	if (shape.getGlobalBounds().intersects(w1.getGlobalBounds()))
		lives--;
}

int main()
{
	int keyonoff(1);
	const int w(1200);
	const int h(600);
	const float radius(30);
	float x(w / 2 - radius);
	float y(h / 2 - radius);

	sf::RenderWindow window(sf::VideoMode(w, h), "Nasze okno");

	//gracz
	sf::CircleShape shape(radius, 3);
	shape.rotate(-30);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(radius, radius);
	shape.setPosition(radius, h/2 + 50);
	sf::Vector2f Speed1(5, 5);


	//pocisk
	sf::RectangleShape bullet(sf::Vector2f(20, 10));
	bullet.setFillColor(sf::Color::Black);
	bullet.setPosition(-10, -10);
	sf::Vector2f Speed2(30, 0);


	//pocisk 2
	sf::RectangleShape bullet2(sf::Vector2f(20, 10));
	bullet2.setFillColor(sf::Color::Black);
	bullet2.setPosition(-10, -10);
	sf::Vector2f Speed3(30, 0);

	//wrog
	sf::CircleShape w1(radius + 10);
	w1.setFillColor(sf::Color::Red);
	w1.setOrigin(radius+10, radius+10);
	w1.setPosition(w + radius * 2, h / 2);
	sf::Vector2f sw1(-5, 5);

	//scoreboard
	sf::RectangleShape board(sf::Vector2f(w, 100));
	board.setFillColor(sf::Color(0,25,152,255));
	board.setPosition(0, 0);

	//tekst
	sf::Font ttf;
	ttf.loadFromFile("fonts/OpenSans-Bold.ttf");
	stringstream s;
	s << "SCORE: " << score;
	stringstream l;
	l << "HP: " << lives;
	sf::Text text(s.str().c_str(), ttf);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Black);
	text.setPosition(10, 10);
	
	sf::Text lives(l.str().c_str(), ttf);
	lives.setCharacterSize(25);
	lives.setFillColor(sf::Color::Black);
	lives.setPosition(w - lives.getGlobalBounds().width - 10, 10);

	sf::Text title("STAR SHOOTER", ttf);
	title.setCharacterSize(35);
	title.setFillColor(sf::Color::Black);
	title.setPosition(w / 2 - title.getGlobalBounds().width / 2, title.getGlobalBounds().height);



	window.setFramerateLimit(60); //60 fps

	//petla gry
	while (window.isOpen())
	{

		zdarzeniasfml(window, shape, bullet, Speed2, bullet2);

		sf::Vector2f pos1 = shape.getPosition();
		sf::Vector2f pos2 = bullet.getPosition();
		sf::Vector2f pos3 = bullet2.getPosition();

		ruchbohatera(shape, bullet, window, Speed1, Speed2, pos2, pos3, bullet2, text, s);

		kolizje(pos1, radius, window, shape, w1, bullet, bullet2);

		window.clear(sf::Color::Black);

		window.draw(shape);
		window.draw(bullet);
		window.draw(bullet2);
		window.draw(w1);
		window.draw(board);
		window.draw(text);
		window.draw(lives);
		window.draw(title);


		window.display();
	}

	return 0;
}
