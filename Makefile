NAME = ircserv

SRCS =		Config.cpp main.cpp Server.cpp utils.cpp User.cpp Channel.cpp
INCLUDES =	Config.hpp Server.hpp utils.hpp User.hpp Channel.hpp

OBJ = $(SRCS:.cpp=.o)

CC = c++

FLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME) $(INCLUDES)

$(NAME): $(OBJ) $(INCLUDES)
			$(CC) $(FLAGS) $(OBJ) -std=c++98 -o $(NAME)

%.o : %.cpp
			$(CC) $(FLAGS) -c $< -o $@

clean:
			${RM} ${OBJ}

fclean: clean
			$(RM) -rf $(NAME)

re: fclean all