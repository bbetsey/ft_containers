# include "srcs/containers/vector.hpp"


int	main( void ) {
	ft::vector<int> vec( 5 );

	std::cout << vec.front() << std::endl;
	std::cout << vec.back() << std::endl;

	vec.back() = 5;
	std::cout << "New last element: " << vec.back() << std::endl;

	std::cout << "\n----- Capacity testing -----" << std::endl;
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << "Max Size: " << vec.max_size() << std::endl;



	return 0;
}
