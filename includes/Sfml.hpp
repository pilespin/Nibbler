
#pragma once

class Shared;

class Sfml : public IGraphic {

public:
	Sfml();
	~Sfml();
	Sfml(Sfml const &src);
	Sfml &operator=(Sfml const &rhs);

	int			getValue() const;
	void		empty();

 void	init();
 void	quit();
 void	draw();
 int	getKey();
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
	int _val;
};

std::ostream &operator<<(std::ostream &o, Sfml &c);
