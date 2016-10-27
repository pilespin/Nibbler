
#pragma once

class Shared;

class Sfml : public IGraphic {

public:
	Sfml();
	virtual ~Sfml();
	Sfml(Sfml const &src);
	Sfml &operator=(Sfml const &rhs);

	int			getValue() const;
	void		empty();

	void	init();
	void	quit();
	void	draw();
	int		getKey();
	void	setShared(Shared *shared);
	void	setWindowSize(int y, int x);
	void	setWindowName(std::string name);

	class Error : public std::exception {
	public:
		Error(std::string str) { 
			this->line += str; 
		}
		virtual const char *what() const throw() {
			return (this->line.c_str());
		}
	private:
		std::string line;
	};

private:
	sf::RenderWindow window;
	std::map< std::string, sf::Texture > 	img;
	int _val;

	void	loadImage(std::string path, std::string name);
 	std::vector<sf::RectangleShape>  constructobject();
sf::RectangleShape make_obj(int X, int Y, std::string texture);

};

std::ostream &operator<<(std::ostream &o, Sfml &c);
