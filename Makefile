NAME = ircserv

SRCS =		Nick.cpp ACommand.cpp Config.cpp Server.cpp utils.cpp User.cpp Channel.cpp main.cpp 
INCLUDES =	Nick.hpp ACommand.hpp Config.hpp Server.hpp utils.hpp User.hpp Channel.hpp

OBJDIR := objs

OBJ = $(SRCS:%.cpp=%.o)

vpath %.cpp srcs srcs/commands
vpath %.hpp hdrs hdrs/commands
vpath %.o $(OBJDIR)

CC = c++

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix $(OBJDIR)/, $(OBJ)) -Ihdrs -Ihdrs/commands -std=c++98 -o $(NAME)

%.o : %.cpp | $(OBJDIR) $(INCLUDES)
	$(CC) $(FLAGS) -Ihdrs -Ihdrs/commands -c $< -o $(OBJDIR)/$@

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all