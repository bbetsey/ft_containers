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
	vec_origin.assign( 10, 7 );
	vec.assign( vec_origin.begin(), vec_origin.end() );
	std::cout << "10 element is " << vec.at( 10 ) << std::endl;
	std::cout << "Size: " << vec.size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;

	std::cout << "\n----- Insert testing -----" << std::endl;
	vec.clear();
	vec.assign( 10, 5 );
	ft::vector<int>::iterator	it = vec.begin();

	for (; it != vec.end(); ++it)
		std::cout << *it << " ";

	it = vec.begin();
	vec.insert( it + 4, 2 );
	it = vec.begin();
	std::cout << "New size: " << vec.size() << std::endl;
	std::cout << "New capacity: " << vec.capacity() << std::endl;
	std::cout << vec.begin() - vec.end() << std::endl;
	std::cout << *it << std::endl;
	for (; it != vec.end(); ++it)
		std::cout << *it << " ";

	std::cout << "\n** Range Insert **" << std::endl;

	std::vector<int>::iterator	it_origin = vec_origin.begin();
	for (; it_origin != vec_origin.end(); ++it_origin)
		std::cout << *it_origin << " ";
	std::cout << std::endl;

	it = vec.begin();
	it_origin = vec_origin.begin();
	vec.insert( it + 7, vec_origin.begin(), vec_origin.end() );

	std::cout << "New size: " << vec.size() << std::endl;
	
	it = vec.begin();
	for (; it != vec.end(); ++it)
		std::cout << *it << " ";
	

	std::cout << "\n----- Erase Testing -----" << std::endl;
	vec.erase( vec.begin() + 3, vec.begin() +7 );
	it = vec.begin();
	for (; it != vec.end(); ++it)
		std::cout << *it << " ";
	
	std::cout << std::endl << std::endl;

	return 0;
}
