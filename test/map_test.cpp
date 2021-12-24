# include "test.hpp"
# include <iostream>
# include <map>

# define NUMBER		30
# define LOWERBOUND 19
# define UPPERBOUND 20

// void	test( void ) {
// 	ft::map<int, int>				dict;
// 	ft::map<int, int>::iterator		it;
// 	std::map<int, int>				orig;
// 	std::map<int, int>::iterator	it_orig;

// 	std::map<int, int>				data;
// 	for ( int i = 1; i < 11; ++i )
// 		data.insert( std::make_pair( i, i ) );

// 	dict.insert( data.begin(), data.end() );
// 	orig.insert( data.begin(), data.end() );

// 	for ( it_orig = orig.begin() ; it_orig != orig.end(); ++it_orig )
// 		std::cout << it_orig->first << " ";

// 	std::cout << std::endl;

// 	for ( it = dict.begin() ; it != dict.end(); ++it )
// 		std::cout << *it.base()->value << std::endl;
// }


void	constructorTest( void ) {
	ft::map<int, int>::iterator		it;
	std::map<int, int>::iterator	ito;

	ft::map<int, int>	data;
	std::map<int, int>	data1;
	for ( int i = 1, j = 10; i < 300000; ++i, ++j ) {
		data.insert( ft::make_pair( i, j ) );
		data1.insert( std::make_pair( i, j ) );
	}
	
	ft::map<int, int> dict( data.begin(), data.end() );
	std::map<int, int> orig( data1.begin(), data1.end() );

	std::vector<int> vec1;
	std::vector<int> vec2;

	for ( it = dict.begin(); it != dict.end(); ++it ) {
		vec1.push_back( it->first );
		vec1.push_back( it->second );
	}

	for ( ito = orig.begin(); ito != orig.end(); ++ito ) {
		vec2.push_back( ito->first );
		vec2.push_back( ito->second );
	}

	if ( vec1 == vec2 )
		std::cout << "[OK]" << std::endl;
	else
		std::cout << "[FALSE]" << std::endl;
}

void	testFT( void ) {
	ft::map<int, int>				dict;
	ft::map<int, int>::iterator		it;

	std::map<int, int>	data;
	for ( int i = 1; i <= NUMBER; ++i )
		data.insert( std::make_pair( i, i ) );

	dict.insert( data.begin(), data.end() );

	ft::map<int, int> dict1( dict );
	ft::map<int, int> dict2;
	dict2 = dict1;

	dict2.erase( UPPERBOUND );
	for ( it = dict2.begin(); it != dict2.end(); ++it )
		std::cout << it->first << " ";

	std::cout << std::endl;
	std::cout << "Lower Bound:\t" << dict2.lower_bound( LOWERBOUND )->first << std::endl;
	std::cout << "Upper Bound:\t" << dict2.upper_bound( UPPERBOUND )->first << std::endl;

	std::cout << "Begin:\t\t" << dict2.begin()->first << std::endl;
	std::cout << "End:\t\t" << dict2.end()->first << std::endl;
	std::cout << "-- Begin:\t" << (--dict2.begin())->first << std::endl;
}

void	testORIG( void ) {
	std::map<int, int>				dict;
	std::map<int, int>::iterator	it;

	std::map<int, int>	data;
	for ( int i = 1; i <= NUMBER; ++i )
		data.insert( std::make_pair( i, i ) );

	dict.insert( data.begin(), data.end() );

	dict.erase( UPPERBOUND );
	for ( it = dict.begin(); it != dict.end(); ++it )
		std::cout << it->first << " ";

	std::cout << std::endl;
	std::cout << "Lower Bound:\t" << dict.lower_bound( LOWERBOUND )->first << std::endl;
	std::cout << "Upper Bound:\t" << dict.upper_bound( UPPERBOUND )->first << std::endl;
	
	std::cout << "Begin:\t\t" << dict.begin()->first << std::endl;
	std::cout << "End:\t\t" << dict.end()->first << std::endl;
	std::cout << "-- Begin:\t" << (--dict.begin())->first << std::endl;
}

int	main( void ) {

	std::cout << "------------ Test FT ------------" << std::endl;
	testFT();
	std::cout << "----------- Test ORIG -----------" << std::endl;
	testORIG();
	std::cout << "---------------------------------" << std::endl;
	// constructorTest();
	
	return 0;
}
