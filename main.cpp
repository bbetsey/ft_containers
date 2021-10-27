# include "srcs/containers/vector.hpp"
# include <vector>


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

	std::cout << "\n----- Reserve testing -----" << std::endl;
	vec.reserve( 10 );
	std::cout << "Capacity: " << vec.capacity() << std::endl;

	std::cout << "\n----- Clear testing -----" << std::endl;
	vec.clear();
	std::cout << "Size: " << vec.size() << std::endl;

	std::cout << "\n----- Assign testing -----" << std::endl;
	vec.assign( 50, 12 );
	std::cout << "20 element is " << vec.at( 20 ) << std::endl;
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;

	std::vector<int> vec_origin;
	vec_origin.assign( 20, 7 );
	vec.assign( vec_origin.begin(), vec_origin.end() );
	std::cout << "10 element is " << vec.at( 10 ) << std::endl;
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;

	return 0;
}
