
#include <project.hpp>
#include "IGraphic.hpp"
#include "Shared.hpp"
#include "Object.hpp"
#include "Sfml.hpp"

Sfml::Sfml() 						{	this->_val = 0;	}

Sfml::~Sfml()						{}

Sfml::Sfml(Sfml const &src)	{	
	this->_val = src._val;
}

Sfml	&Sfml::operator=(Sfml const &rhs) {

	if (this != &rhs)
	{
		this->_val = rhs._val;
	}
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Sfml &c) {
	o << "Sfml: " << c.getValue() << " ";
	return (o);
}
///////////////////////////////////////////////////////////////////////////////
int		Sfml::getValue() const			{	return (this->_val);	}
void	Sfml::setShared(Shared *shared)	{	this->shared = shared;		}
///////////////////////////////////////////////////////////////////////////////

void	init() {

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

void	quit() {

}

void	draw() {

}

int		getKey() {
return(1);
}

void	setWindowSize(int y, int x) {
(void)x;
(void)y;
}

void	setWindowName(std::string name) {
(void)name;
}


void	Sfml::empty() {

}

extern "C"
{
	IGraphic *make_class()
	{
		return new Sfml();
	}
}