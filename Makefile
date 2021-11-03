NAME	= containers
SRCS	= main.cpp test/vector_test.cpp

OBJS	= $(SRCS:.cpp=.o)
INC		= -I srcs/containers/ -I srcs/iterators/ -I srcs/utils/
FLAGS	= -Wall -Wextra -Werror -std=c++98

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
