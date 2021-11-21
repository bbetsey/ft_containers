#include "test.hpp"
# include <ostream>

void	startTest( const std::string &testName ) {
	// std::cout << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << BOLDWHITE;
	std::cout << "\n» " << testName << std::endl << std::endl;
	std::cout << RESET;
}

template < class T >
bool	compare( ft::vector<T> &vec, std::vector<T> &orig ) {
	typename ft::vector<T>::iterator it_vec = vec.begin();
	typename std::vector<T>::iterator it_orig = orig.begin();

	for (; it_vec != vec.end(); ++it_vec, ++it_orig ) {
		if ( *it_vec != *it_orig )
			return false;
	}
	if ( vec.size() != orig.size() )
		return false;
	return true;
}

template < class T >
void	result( ft::vector<T> &vec, std::vector<T> &orig ) {
	if ( compare<T>( vec, orig ) )
		std::cout << BOLDGREEN << "[OK]" << RESET << std::endl;
	else
		std::cout << BOLDRED << "[ERROR]" << RESET << std::endl;
}

template < class T >
void	printVector( ft::vector<T> &vec, std::vector<T> &orig ) {
	std::cout << "vec:\t";
	for ( typename ft::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it )
		std::cout << *it << " ";
	std::cout << std::endl << "orig:\t";
	for ( typename std::vector<T>::iterator it = orig.begin(); it != orig.end(); ++it )
		std::cout << *it << " ";
	std::cout << std::endl << std::endl;
}


template < class T, T value >
void	assignTest( void ) {

	startTest( "ASSIGN Test" );

	{
		ft::vector<T>	vec;
		std::vector<T>	orig;

		vec.assign( 10, value );
		orig.assign( 10, value );

		std::cout << MAGENTA << "Value » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec;
		std::vector<T>	orig;

		std::vector<T>	tmp( 10, value );

		vec.assign( tmp.begin(), tmp.end() );
		orig.assign( tmp.begin(), tmp.end() );

		std::cout << MAGENTA << "Range » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}


}

template < class T >
void	constructorsTest( void ) {

	startTest( "CONSTRUCTORS Test" );

	{
		ft::vector<T>	vec;
		std::vector<T>	orig;

		std::cout << MAGENTA << "Default Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Count Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	tmp( 10 );
		std::vector<T>	tmp_orig( 10 );

		ft::vector<T>	vec( tmp.begin(), tmp.end() );
		std::vector<T>	orig( tmp_orig.begin(), tmp_orig.end() );

		std::cout << MAGENTA << "Range Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	tmp( 10 );
		std::vector<T>	tmp_orig( 10 );

		ft::vector<T>	vec( tmp );
		std::vector<T>	orig( tmp_orig );

		std::cout << MAGENTA << "Copy Constructor » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	tmp( 10 );
		std::vector<T>	tmp_orig( 10 );

		ft::vector<T>	vec = tmp;
		std::vector<T>	orig = tmp_orig;

		std::cout << MAGENTA << "Assignation Overload » " << RESET;
		result( vec, orig );
		printVector( vec, orig );
	}
}

template < class T >
void	resize_test( void ) {

	startTest( "Resize Test" );

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Resize [10 -> 100] » " << RESET;
		vec.resize( 100, 45 );
		orig.resize( 100, 45 );
		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Resize [10 -> 2] » " << RESET;
		vec.resize( 2, 45 );
		orig.resize( 2, 45 );
		result( vec, orig );
		printVector( vec, orig );
	}
}

template < class T >
void	insert_test( void ) {

	startTest( "Insert Test" );

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Insert [+5; 3] » " << RESET;
		vec.insert( vec.begin() + 5, 3 );
		orig.insert( orig.begin() + 5, 3 );

		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );

		std::cout << MAGENTA << "Insert [+10; 4; 3] » " << RESET;
		vec.insert( vec.begin() + 10, 4, 3 );
		orig.insert( orig.begin() + 10, 4, 3 );

		result( vec, orig );
		printVector( vec, orig );
	}

	{
		ft::vector<T>	vec( 10 );
		std::vector<T>	orig( 10 );
		std::vector<int>	tmp;

		for( int i = 0; i < 5; ++i )
			tmp.push_back( i * i );

		std::cout << MAGENTA << "Insert [+10; tmp.begin(); tmp.end()] » " << RESET;
		vec.insert( vec.begin() + 10, tmp.begin(), tmp.end() );
		orig.insert( orig.begin() + 10, tmp.begin(), tmp.end() );

		result( vec, orig );
		printVector( vec, orig );
	}
}

void	vectorTest( void ) {
	constructorsTest<float>();
	assignTest<int, 70>();
	resize_test<int>();
	insert_test<int>();
}
