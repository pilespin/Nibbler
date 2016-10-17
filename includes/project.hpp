/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 18:48:50 by pilespin          #+#    #+#             */
/*   Updated: 2016/10/17 13:57:51 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_H
# define PROJECT_H

enum eCommand {None, Lib1, Lib2, Lib3, Up, Down, Left, Right, Escape};

#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <map>
#include <dlfcn.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <sys/time.h>
#include <iomanip>

#define BLOCK	3
#define APPLE	2
#define SNAKE	1
#define OFF 	0

#endif