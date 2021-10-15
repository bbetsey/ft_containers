NAME	= containers
SRCS	= main.cpp
OBJS	= $(SRCS:.cpp=.o)
INC		= -I
FLAGS	= -Wall -Wextra -Werror -W -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	clang++ $(FLAGS) $(INC) $(OBJS) -o $(NAME)

%.o: %.cpp
	clang++ $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
