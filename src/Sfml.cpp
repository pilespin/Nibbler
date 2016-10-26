#include <SFML/Graphics.hpp>
#include <project.hpp>
#include "IGraphic.hpp"
#include "Shared.hpp"
#include "Object.hpp"
#include "Sfml.hpp"

Sfml::Sfml() 						{	this->_val = 0;	}

Sfml::~Sfml()						{}

Sfml::Sfml(Sfml const &src)	{	
    this->_val          = src._val;
    this->shared        = src.shared;
    this->windowName    = src.windowName;
    this->squareSize    = src.squareSize;
    this->windowSizeX   = src.windowSizeX;
    this->windowSizeY   = src.windowSizeY;
    this->last_time     = src.last_time;
}

Sfml	&Sfml::operator=(Sfml const &rhs) {

	if (this != &rhs)
	{
        this->_val          = rhs._val;
        this->shared        = rhs.shared;
        this->windowName    = rhs.windowName;
        this->squareSize    = rhs.squareSize;
        this->windowSizeX   = rhs.windowSizeX;
        this->windowSizeY   = rhs.windowSizeY;
        this->last_time     = rhs.last_time;
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

void	Sfml::init() {

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

void	Sfml::quit() {

}

void	Sfml::draw() {

}

int		Sfml::getKey() {
    return(1);
}

void	Sfml::setWindowSize(int y, int x) {
    (void)x;
    (void)y;
}

void	Sfml::setWindowName(std::string name) {
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
