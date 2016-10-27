# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/15 18:31:49 by pilespin          #+#    #+#              #
#    Updated: 2016/10/18 19:27:43 by pilespin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all compil clean fclean re run
	
NAME	=	nibbler

CC		=	g++ -std=c++11 -g
FLAGS	=	-Wall -Wextra -Werror
LIB		=	-ldl -lpthread

NCURSES		= -lncurses

LIB_SDL 		= SDL
PATH_SDL 		= SDL2-2.0.5
PATH_SDL_IMG 	= SDL2_image-2.0.1
SDL 			= `./$(LIB_SDL)/bin/sdl2-config --cflags --libs` -lSDL2_image

LIB_QT 		= /goinfre/qtbase
PATH_QT 	= /goinfre/qt-everywhere-opensource-src-5.7.0
QT 			= 

LIB_SFML 	= SFML
PATH_SFML 	= SFML-2.4.0
SFML 		= -Xlinker -rpath -Xlinker ./$(PATH_SFML)/lib/ -L./$(PATH_SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

SDIR	=	src/
HDIR	=	includes/
ODIR	=	obj/
F_EXT	=	cpp
H_EXT	=	hpp

ifeq ($(shell uname), Darwin)
FOLDER	=	-I $(HDIR) -I./$(LIB_SDL)/include -I./$(LIB_SDL)/lib/ -I./$(PATH_SFML)/include/
else
FOLDER	=	-I $(HDIR) -I./$(LIB_SDL)/include -I./$(LIB_SDL)/lib/ -I./$(PATH_SFML)/usr/local/include/
endif

# SRCA	=	$(shell cd $(SDIR) && ls -1 *.$(F_EXT))
SRCA	=	main.cpp DynamicLib.cpp Core.cpp Shared.cpp Object.cpp

SRCH	=	$(shell cd $(HDIR) && ls -1 *.$(H_EXT))
SRCO	=	$(SRCA:$(F_EXT)=.o)

SRC 	=	$(patsubst %.$(F_EXT), $(SDIR)%.$(F_EXT), $(SRCA))
HDR		=	$(patsubst %.$(H_EXT), $(HDIR)%.$(H_EXT), $(SRCH))
OBJ		=	$(patsubst %.$(F_EXT), $(ODIR)%.o, $(SRCA))

all: sdl sfml compil

no: compil

sfml:
	@echo "\033[32mDownloading SFML ...\033[0m"
	@curl http://mirror2.sfml-dev.org/files/SFML-2.4.0-sources.zip -o $(PATH_SFML).zip
	@echo "\033[32mCompiling SFML...\033[0m"
	@unzip $(PATH_SFML).zip
	@cat patch_sfml > $(PATH_SFML)/src/SFML/Graphics/CMakeLists.txt
ifeq ($(shell uname), Darwin)
	@cd $(PATH_SFML) && cmake -DCMAKE_INSTALL_PREFIX=/Library/Frameworks/Mono.framework/Headers/freetype2/ . && make -j 8 && make -j 8 install DESTDIR=./
	@cp -r $(PATH_SFML)/Library/Frameworks $(PATH_SFML)
else
	@cd $(PATH_SFML) && cmake . && make -j 8 && make - j 8 install DESTDIR=./
endif
	@rm -rf $(PATH_SFML).zip

qt:
	@curl http://www.mirrorservice.org/sites/download.qt-project.org/archive/qt/5.7/5.7.0/single/qt-everywhere-opensource-src-5.7.0.tar.gz -o $(PATH_QT).tar.gz
	mkdir -p $(LIB_QT)
	tar -xf $(PATH_QT).tar.gz -C /goinfre/
	cd $(PATH_QT) && ./configure --prefix=`cd $(LIB_QT) && pwd` -opensource -nomake tests -nomake examples -release -confirm-license && make -j 8

sdl:
	@echo "\033[32mDownloading SDL ...\033[0m"
	@curl https://www.libsdl.org/release/SDL2-2.0.5.tar.gz -o $(PATH_SDL).tar.gz
	@curl https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1.tar.gz -o $(PATH_SDL_IMG).tar.gz
	@echo "\033[32mCompiling SDL ...\033[0m"
	@mkdir -p $(LIB_SDL)
	@tar -xf $(PATH_SDL).tar.gz
	@tar -xf $(PATH_SDL_IMG).tar.gz
	@cd $(PATH_SDL) && ./configure --prefix=`cd ../$(LIB_SDL) && pwd` && make -j 8 && make -j 8 install
	@cd $(PATH_SDL_IMG) && ./configure --prefix=`cd ../$(LIB_SDL) && pwd` && make -j 8 && make -j 8 install
	@rm -rf $(PATH_SDL)
	@rm -rf $(PATH_SDL_IMG)
	@rm -rf $(PATH_SDL_IMG).tar.gz
	@rm -rf $(PATH_SDL).tar.gz

compil:
	@mkdir -p $(ODIR)
	@echo "\033[32m compiling $(NAME) >>> \c \033[0m"
	@make -j 8 dynlib
	@make -j 8 $(NAME)

$(NAME): $(OBJ) $(SRC)
	@$(CC) -o $(NAME) $(OBJ) $(LIB) $(FOLDER)
	@echo "\033[37m END $(NAME)\033[0m"

$(ODIR)%.o: $(SDIR)%.$(F_EXT) $(HDR) 
	@$(CC) -c $< -o $@ $(FLAGS) $(FOLDER)
	@echo "\033[32m ok \033[33m $@\033[0m"

dynlib:
	@$(CC) -shared -o libmysdl.so src/Sdl.cpp src/Object.cpp $(FLAGS) $(SDL) $(FOLDER) -fPIC
	@$(CC) -shared -o libmyncurses.so src/Ncurses.cpp src/Object.cpp $(FLAGS) $(NCURSES) $(FOLDER) -fPIC
	@$(CC) -shared -o libmysfml.so src/Sfml.cpp src/Object.cpp $(FLAGS) $(SFML) $(FOLDER) -fPIC
	@echo "\033[32m ok \033[33m dynlib \033[0m"

clean:
	@rm -rf $(ODIR)
	@rm -rf $(PATH_SDL)
	@rm -rf $(PATH_SDL).tar.gz
	@rm -rf $(PATH_SDL_IMG)
	@rm -rf $(PATH_SDL_IMG).tar.gz

fclean: clean
	@rm -f $(NAME)
	@rm -f libmysdl.so
	@rm -f libmyncurses.so
	@rm -f libmysfml.so
	@rm -rf $(LIB_SDL)
	@rm -rf $(LIB_SFML)
	@rm -rf $(PATH_SFML).zip
	@rm -rf $(PATH_SFML)

re: fclean all

run:
	@clear
	@make no
	@./$(NAME)

leaks:
	@zsh -c "while ((1)) {sleep 1 ; leaks $(NAME) | grep -A 1 Leak > the_leaks ; clear && cat the_leaks}"

allleaks:
	@zsh -c "while ((1)) {sleep 1 ; leaks $(NAME) > the_leaks ; clear && cat the_leaks}"


coffee:
	@clear
	@echo "                        \`:.      				"
	@echo "                          \`:.      				"
	@echo "                  .:'     ,::      				"
	@echo "                 .:'      ;:'      				"
	@echo "                 ::      ;:'      				"
	@echo "                  :    .:'      					"
	@echo "                   \`.  :.      					"
	@echo "          _________________________      		"
	@echo "         : _ _ _ _ _ _ _ _ _ _ _ _ :      		"
	@echo "     ,---:\".\".\".\".\".\".\".\".\".\".\".\".\":"
	@echo "    : ,'\"\`::.:.:.:.:.:.:.:.:.:.:.::'      		"
	@echo "    \`.\`.  \`:-===-===-===-===-===-:'      		"
	@echo "      \`.\`-._:                   :      		"
	@echo "        \`-.__\`.               ,'      			"
	@echo "    ,--------\`\"\`-------------'--------.      	"
	@echo "     \`\"--.__                   __.--\"'   	   	"
	@echo "            \`\"\"-------------\"\"'    			"
	@echo "    											  	"
	@sleep 0.5
	@clear
	@echo "                       \`:.      				"
	@echo "                          \`:.      				"
	@echo "                   .:'     ,::      				"
	@echo "                .:'        ;:'      				"
	@echo "                ::        ;:'      				"
	@echo "                 :      .:'      				"
	@echo "                  \`.    :.      				"
	@echo "          _________________________      		"
	@echo "         : _ _ _ _ _ _ _ _ _ _ _ _ :      		"
	@echo "     ,---:\".\".\".\".\".\".\".\".\".\".\".\".\":"
	@echo "    : ,'\"\`::.:.:.:.:.:.:.:.:.:.:.::'      		"
	@echo "    \`.\`.  \`:-===-===-===-===-===-:'      		"
	@echo "      \`.\`-._:                   :      		"
	@echo "        \`-.__\`.               ,'      			"
	@echo "    ,--------\`\"\`-------------'--------.      	"
	@echo "     \`\"--.__                   __.--\"'   	   	"
	@echo "            \`\"\"-------------\"\"'    			"
