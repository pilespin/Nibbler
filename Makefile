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

LIB_SDL 	= SDL
PATH_SDL 	= SDL2-2.0.4
SDL 		= `./$(LIB_SDL)/bin/sdl2-config --cflags --libs`

LIB_ALLEGRO 	= ALLEGRO
PATH_ALLEGRO 	= allegro-5.2.1.1
ALLEGRO 		= `./$(LIB_ALLEGRO)/allegro-config --cflags --libs`

SDIR	=	src/
HDIR	=	includes/
ODIR	=	obj/
F_EXT	=	cpp
H_EXT	=	hpp
FOLDER	=	-I $(HDIR) -I./$(LIB_SDL)/include -I./$(LIB_ALLEGRO)/include

# SRCA	=	$(shell cd $(SDIR) && ls -1 *.$(F_EXT))
SRCA	=	main.cpp DynamicLib.cpp Core.cpp Shared.cpp Object.cpp

SRCH	=	$(shell cd $(HDIR) && ls -1 *.$(H_EXT))
SRCO	=	$(SRCA:$(F_EXT)=.o)

SRC 	=	$(patsubst %.$(F_EXT), $(SDIR)%.$(F_EXT), $(SRCA))
HDR		=	$(patsubst %.$(H_EXT), $(HDIR)%.$(H_EXT), $(SRCH))
OBJ		=	$(patsubst %.$(F_EXT), $(ODIR)%.o, $(SRCA))

all: allegro compil

no: compil

allegro:
	@echo "\033[32mDownloading Allegro ...\033[0m"
	curl http://download.gna.org/allegro/allegro/5.2.1.1/allegro-5.2.1.1.tar.gz -o $(PATH_ALLEGRO).tar.gz
	@echo "\033[32mCompiling Allegro ...\033[0m"
	@mkdir -p $(LIB_ALLEGRO)
	@tar -xf $(PATH_ALLEGRO).tar.gz
	@cd $(LIB_ALLEGRO) && cmake -DSHARED=0 ../$(PATH_ALLEGRO) && make
	@rm -rf $(PATH_ALLEGRO)
	@rm -rf $(PATH_ALLEGRO).tar.gz

sdl:
	@echo "\033[32mDownloading SDL ...\033[0m"
	curl https://www.libsdl.org/release/SDL2-2.0.4.tar.gz -o $(PATH_SDL).tar.gz
	@echo "\033[32mCompiling SDL ...\033[0m"
	@mkdir -p $(LIB_SDL)
	@tar -xf $(PATH_SDL).tar.gz
	@cd $(PATH_SDL) && ./configure --prefix=`cd ../$(LIB_SDL) && pwd` && make && make install
	@rm -rf $(PATH_SDL)
	@rm -rf $(PATH_SDL).tar.gz

compil:
	@mkdir -p $(ODIR)
	@echo "\033[32m compiling $(NAME) >>> \c \033[0m"
	@make dynlib
	@make $(NAME)

$(NAME): $(OBJ) $(SRC)
	@$(CC) -o $(NAME) $(OBJ) $(LIB) $(FOLDER)
	@echo "\033[37m END $(NAME)\033[0m"

$(ODIR)%.o: $(SDIR)%.$(F_EXT) $(HDR) 
	@$(CC) -c $< -o $@ $(FLAGS) $(FOLDER)
	@echo "\033[32m ok \033[33m $@\033[0m"

dynlib:
	@$(CC) -shared -o libmysdl.so src/Sdl.cpp src/Object.cpp $(FLAGS) $(SDL) $(FOLDER) -fPIC
	@$(CC) -shared -o libmyncurses.so src/Ncurses.cpp src/Object.cpp $(FLAGS) $(NCURSES) $(FOLDER) -fPIC
	@$(CC) -shared -o libmyallegro.so src/Allegro.cpp $(ALLEGRO) $(FLAGS) $(FOLDER) -fPIC
	@echo "\033[32m ok \033[33m dynlib \033[0m"

clean:
	@rm -rf $(ODIR)
	@rm -rf $(PATH_SDL)
	@rm -rf $(PATH_SDL).tar.gz
	@rm -rf $(LIB_ALLEGRO)
	@rm -rf $(PATH_ALLEGRO)
	@rm -rf $(PATH_ALLEGRO).tar.gz

fclean: clean
	@rm -f $(NAME)
	@rm -f libmysdl.so

re: fclean all

run:
	@clear
	@make no
	@./$(NAME)

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
