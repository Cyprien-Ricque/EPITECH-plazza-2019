##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Compile cpp files
##

NAME			=	plazza

SRC				= 	src/main.cpp							\
					src/classes/Cooker.cpp					\
					src/classes/IPC.cpp						\
					src/classes/Kitchen.cpp					\
					src/classes/PlazzaParser.cpp			\
					src/classes/Reception.cpp				\
					src/classes/PizzaFactory.cpp			\
					src/classes/MessageQueue.cpp			\
					src/classes/dataPizza.cpp				\
					src/classes/ConditionalVariables.cpp	\
					src/classes/Mutex.cpp					\
					src/classes/Clock.cpp					\
					src/classes/Thread.cpp					\
					src/classes/Process.cpp					\
					src/classes/Logs.cpp					\
					src/classes/AsyncGetline.cpp

OBJ				=	$(SRC:.cpp=.o)

CC 				= 	g++

CXXFLAGS    	+=	-W -Wall -Wextra -Wno-unused
CXXFLAGS    	+=	-I include

all:        	$(NAME)

$(NAME):    	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS) -lpthread

debug: 	CXXFLAGS += -g
debug:	all

debugre: CXXFLAGS += -g
debugre: re

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re: 		fclean all
