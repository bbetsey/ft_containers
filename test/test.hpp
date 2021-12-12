#ifndef TEST_HPP
# define TEST_HPP

# include <iostream>
# include <vector>
# include "../srcs/containers/vector.hpp"
# include "../srcs/containers/map.hpp"

# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"
# define BOLDBLACK		"\033[1m\033[30m"
# define BOLDRED		"\033[1m\033[31m"
# define BOLDGREEN		"\033[1m\033[32m"
# define BOLDYELLOW		"\033[1m\033[33m"
# define BOLDBLUE		"\033[1m\033[34m"
# define BOLDMAGENTA	"\033[1m\033[35m"
# define BOLDCYAN		"\033[1m\033[36m"
# define BOLDWHITE		"\033[1m\033[37m"

void	vectorTest( void );

void	startTest( const std::string &testName ) {
	// std::cout << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << BOLDWHITE;
	std::cout << "\n» " << testName << std::endl << std::endl;
	std::cout << RESET;
}


#endif
