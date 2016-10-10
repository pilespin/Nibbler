
#pragma once

#include <project.hpp>

class DynamicLib {

public:
	DynamicLib();
	~DynamicLib();
	DynamicLib(DynamicLib const &src);
	DynamicLib &operator=(DynamicLib const &rhs);

	int			getValue() const;
	void		*getClass() const;

	void		empty();
	void		*createClass(std::string pathLib);
	void		closeLib();

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
	int 	_val;
	void	*lib;
	void	*ptrClass;
};

std::ostream &operator<<(std::ostream &o, DynamicLib &c);
