/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 18:48:50 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/18 18:43:17 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_H
# define PROJECT_H

enum eCommand 	{None, Left, Right, Up, Down, Escape};
enum eChoseLib 	{Nope, Lib1, Lib2, Lib3};

#include <iostream>
#include <list>
#include <map>
#include <dlfcn.h>
#include <thread>
#include <chrono>
#include <sys/time.h>
#include <iomanip>

#define SDL		1
#define NCURSES	2
#define SFML	3

#define IASNAKE	4
#define BLOCK	3
#define APPLE	2
#define SNAKE	1
#define OFF 	0

#endif