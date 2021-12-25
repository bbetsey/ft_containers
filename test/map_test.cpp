# include "test.hpp"
# include <iostream>
# include <map>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

# define NUMBER		30
# define LOWERBOUND 19
# define UPPERBOUND 20


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

	dict2.erase( dict2.begin() );
	dict2.erase( 30 );
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

	dict.erase( dict.begin() );
	dict.erase( 30 );
	for ( it = dict.begin(); it != dict.end(); ++it )
		std::cout << it->first << " ";

	std::cout << std::endl;
	std::cout << "Lower Bound:\t" << dict.lower_bound( LOWERBOUND )->first << std::endl;
	std::cout << "Upper Bound:\t" << dict.upper_bound( UPPERBOUND )->first << std::endl;
	
	std::cout << "Begin:\t\t" << dict.begin()->first << std::endl;
	std::cout << "End:\t\t" << dict.end()->first << std::endl;
	std::cout << "-- Begin:\t" << (--dict.begin())->first << std::endl;
}

std::map<int, int>	makeRandomMap( void ) {
	int low_dist  = 1;
	int high_dist = 100;
	std::srand( ( unsigned int )std::time( nullptr ) );

	std::map<int, int>	data;
	for ( int i = 1; i <= NUMBER; ++i )
		data.insert( std::make_pair( low_dist + std::rand() % ( high_dist - low_dist ), i ) );
	return data;
}

void	eraseTest( ft::map<int, int> mp, std::map<int, int> mpo ) {

	std::cout << "----------- Test ERASE -----------" << std::endl;

	ft::map<int, int>::iterator		it = mp.begin();
	std::map<int, int>::iterator	ito = mpo.begin();

	mp.erase( mp.begin() );
	mpo.erase( mpo.begin() );
	mp.erase( mp.last() );
	mpo.erase( (--mpo.end()) );

	for ( it = mp.begin(), ito = mpo.begin(); it != mp.end(); ++it, ++ito )
		std::cout << "Orig: " << ito->first << " \tFT: " << it->first << std::endl;	
}

void	iteratorTest( void ) {
	std::map<int, int>	orig;
	ft::map<int, int>	dict;

	std::map<int, int>	data = makeRandomMap();
	
	dict.insert( data.begin(), data.end() );
	orig.insert( data.begin(), data.end() );

	std::map<int, int>::iterator	it_orig = orig.begin();
	ft::map<int, int>::iterator		it_ft = dict.begin();

	for ( ; it_ft != dict.end(); ++it_orig, ++it_ft ) {
		std::cout << "Orig: " << it_orig->first << " \tFT: " << it_ft->first << std::endl;
	}

	std::cout << "------- reverse -------" << std::endl;

	std::cout << "Orig: " << it_orig->first << " \tFT: " << it_ft->first << std::endl;

	std::map<int, int>::reverse_iterator	rit_orig( it_orig );
	ft::map<int, int>::reverse_iterator		rit_ft( it_ft );

	for ( ; rit_ft.base() != dict.begin(); ++rit_ft, ++rit_orig )
		std::cout << "Orig: " << rit_orig->first << "  \tFT: " << rit_ft->first << std::endl;
	
	eraseTest( dict, orig );
}

void	reverseIteratorTest( void ) {
	ft::map<int, int>	mp;
	std::map<int, int>	mpo;

	mp.insert( ft::make_pair( 5, 5 ) );
	mp.insert( ft::make_pair( 3, 3 ) );
	mp.insert( ft::make_pair( 7, 7 ) );
	mpo.insert( std::make_pair( 5, 5 ) );
	mpo.insert( std::make_pair( 3, 3 ) );
	mpo.insert( std::make_pair( 7, 7 ) );

	ft::map<int, int>::reverse_iterator		rit = mp.rbegin();
	ft::map<int, int>::reverse_iterator		rit2 = mp.rend();
	std::map<int, int>::reverse_iterator	rito = mpo.rbegin();
	std::map<int, int>::reverse_iterator	rito2 = mpo.rend();

	std::cout << "Orig: " << rito->first << " \tFT: " << rit->first << std::endl;
	++rit; ++rito;
	--rit2; --rito2;
	std::cout << "Orig: " << rito->first << " \tFT: " << rit->first << std::endl;
	std::cout << "Orig: " << rito2->first << " \tFT: " << rit2->first << std::endl;

}


int	main( void ) {

	std::cout << std::endl;
	std::cout << "------------ Test FT ------------" << std::endl;
	testFT();
	std::cout << "----------- Test ORIG -----------" << std::endl;
	testORIG();
	std::cout << "----------- Test ITER -----------" << std::endl;
	iteratorTest();
	std::cout << "----------- Test REV ITER -----------" << std::endl;
	reverseIteratorTest();
	std::cout << "---------------------------------" << std::endl;
	// constructorTest();
	
	return 0;
}
