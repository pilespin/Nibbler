#include <SFML/Graphics.hpp>
#include <project.hpp>
#include "IGraphic.hpp"
#include "Shared.hpp"
#include "Object.hpp"
#include "Sfml.hpp"

Sfml::Sfml() 						{	
    this->squareSize    = 28;
    this->_val = 0;	
    
    this->loadImage("img/squareyellow.png", "squareyellow");
    this->loadImage("img/squareGreen.bmp", "squareGreen");
    this->loadImage("img/squareblue.png", "squareblue");
    this->loadImage("img/pnoyelle.png", "pnoyelle");
    this->loadImage("img/boobs.png", "boobs");
    this->loadImage("img/rock.png", "rock");
}

Sfml::~Sfml()						{
        if (this->window.isOpen())
            this->window.close();
}

Sfml::Sfml(Sfml const &src)	{	
    this->_val          = src._val;
    this->shared        = src.shared;
    this->windowName    = src.windowName;
    this->squareSize    = 28;
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
        this->squareSize    = 28;
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
void	Sfml::setShared(Shared *shared)	{	
    std::cout<<"abc"<<std::endl;
    this->shared = shared;		
    std::cout<<"abc"<<std::endl;
}
///////////////////////////////////////////////////////////////////////////////

void	Sfml::init() {

    // sf::RenderWindow window(sf::VideoMode(this->shared->mapSizeX * this->squareSize, this->shared->mapSizeY * this->squareSize), "SFML works!");
    std::cout << this->shared->mapSizeX * this->squareSize << "  "<< this->shared->mapSizeY * this->squareSize << std::endl;
    std::cout << this->squareSize << "  "<< this->squareSize << std::endl;
    std::cout << this->shared->mapSizeX << "  "<< this->shared->mapSizeY << std::endl;
    // std::exit(0);
    this->window.create(sf::VideoMode(this->shared->mapSizeX * this->squareSize, this->shared->mapSizeY * this->squareSize), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }
}

void	Sfml::quit() {
    if (this->window.isOpen())
        this->window.close();

}
sf::RectangleShape Sfml::make_obj(int X, int Y, std::string texture){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(this->squareSize, this->squareSize));
        rectangle.setPosition(X * this->squareSize, Y * this->squareSize);
        rectangle.setTexture(&this->img[texture], true);
        return(rectangle);
}

std::vector<sf::RectangleShape>  Sfml::constructobject()
{
    std::vector<sf::RectangleShape> obj;

    for (auto it = this->shared->block.begin(); it != this->shared->block.end(); ++it) {
        obj.push_back(make_obj(it->getX(), it->getY(), "rock"));
        
    }
    for (auto it = this->shared->obj.begin(); it != this->shared->obj.end(); ++it) {
        obj.push_back(make_obj(it->getX(), it->getY(), "boobs"));
    }

    for (auto it = this->shared->snake.begin(); it != this->shared->snake.end(); ++it) {
        obj.push_back(make_obj(it->getX(), it->getY(), "squareGreen"));
    }

    for (auto it = this->shared->IAsnake.begin(); it != this->shared->IAsnake.end(); ++it) {
       sf::RectangleShape rectangle;
        obj.push_back(make_obj(it->getX(), it->getY(), "squareblue"));
    }
    obj.push_back(make_obj(this->shared->IAsnake.begin()->getX(), this->shared->IAsnake.begin()->getY(), "squareyellow"));
    obj.push_back(make_obj(this->shared->snake.begin()->getX(), this->shared->snake.begin()->getY(), "pnoyelle"));

    return (obj);
}

void	Sfml::draw() {
    std::vector<sf::RectangleShape> obj;
    if (this->window.isOpen())
    {

        obj = this->constructobject();
        this->window.clear(sf::Color(175, 95, 255, 255));
        for (size_t i = 0; obj.size() > i; ++i)
        {

            window.draw(obj[i]);
        }
        this->window.display();
    }
    else 
        throw (Error("Window error"));
}

void Sfml::loadImage(std::string path, std::string name)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
        throw(Error("error init Sfml"));
    this->img[name] = texture;
}


int		Sfml::getKey() {
    sf::Event event;

// while there are pending events...
while (window.pollEvent(event))
{
    // check the type of the event...
    switch (event.type)
    {
        // window closed
        case sf::Event::Closed:
            window.close();
            return (eCommand::Escape);

        // key pressed
        case sf::Event::KeyPressed:
            std::cout << event.key.code << std::endl;
            if (event.key.code > 70 && event.key.code < 75)
               shared->setCommand(static_cast<eCommand>(event.key.code - 70));
            else if  (event.key.code == 36)
                shared->setCommand(eCommand::Escape);
            else if (event.key.code == 27 || event.key.code == 28 || event.key.code == 29)
            {
                shared->setLib(static_cast<eChoseLib>(event.key.code - 26));
            }
            break;

        // we don't process other types of events
        default:
            break;
    }
}

    return(1);
}

void	Sfml::setWindowSize(int y, int x) {
    if (x > 0 && x < 16000 && y > 0 && y < 16000)
    {
        this->windowSizeX = x;
        this->windowSizeY = y;
    }
    else
        throw Error("Error: Window size is too small or too big");
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
