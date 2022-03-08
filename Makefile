NAME = ircserv

SRCS_CMD :=		InfoCmd.cpp InviteCmd.cpp JoinCmd.cpp\
				KickCmd.cpp KillCmd.cpp ListCmd.cpp ModeCmd.cpp\
				NamesCmd.cpp NickCmd.cpp OperCmd.cpp PartCmd.cpp\
				PassCmd.cpp PingCmd.cpp PongCmd.cpp PrivmsgNoticeCmd.cpp\
				QuitCmd.cpp RehashCmd.cpp RestartCmd.cpp TopicCmd.cpp UserCmd.cpp VersionCmd.cpp
INCLUDES_CMD :=	InfoCmd.hpp InviteCmd.hpp JoinCmd.hpp\
				KickCmd.hpp KillCmd.hpp ListCmd.hpp ModeCmd.hpp\
				NamesCmd.hpp NickCmd.hpp OperCmd.hpp PartCmd.hpp\
				PassCmd.hpp PingCmd.hpp PongCmd.hpp PrivmsgNoticeCmd.hpp\
				QuitCmd.hpp RehashCmd.hpp RestartCmd.hpp TopicCmd.hpp UserCmd.hpp VersionCmd.hpp
SRCS :=		main.cpp ACommand.cpp Channel.cpp CommandFactory.cpp Config.cpp Error.cpp Message.cpp Server.cpp User.cpp utils.cpp 
INCLUDES :=	ACommand.hpp Channel.hpp CommandFactory.hpp Config.hpp Error.hpp Message.hpp Server.hpp User.hpp utils.hpp

SRCS += $(SRCS_CMD)
INCLUDES += $(INCLUDES_CMD)

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

%.o: %.cpp | $(OBJDIR) $(INCLUDES)
	$(CC) $(FLAGS) -Ihdrs -Ihdrs/commands -c $< -o $(OBJDIR)/$@

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all