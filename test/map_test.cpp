# include "test.hpp"
# include <iostream>
# include <map>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

# define NUMBER		30
# define LOWERBOUND 19
# define UPPERBOUND 20


class MapBoolTest {
public:
	std::map<int, int> m1, m2, m3, m4;
	std::map<std::string, std::string> m5, m6, m7, m8, m9;
	ft::map<int, int> mp1, mp2, mp3, mp4;
	ft::map<std::string, std::string> mp5, mp6, mp7, mp8, mp9;

	MapBoolTest() {
		m1.insert(std::make_pair(2, 3)); mp1.insert(ft::make_pair(2, 3));
		m2.insert(std::make_pair(3, 3)); mp2.insert(ft::make_pair(3, 3));
		m3.insert(std::make_pair(3, 4)); mp3.insert(ft::make_pair(3, 4));
		m4.insert(std::make_pair(4, 4)); mp4.insert(ft::make_pair(4, 4));
		m4.insert(std::make_pair(4, 5)); mp4.insert(ft::make_pair(4, 5));
		m5.insert(std::make_pair("123", "123")); mp5.insert(ft::make_pair("123", "123"));
		m6.insert(std::make_pair("123", "124")); mp6.insert(ft::make_pair("123", "124"));
		m7.insert(std::make_pair("124", "123")); mp7.insert(ft::make_pair("124", "123"));
		m8.insert(std::make_pair("12", "123")); mp8.insert(ft::make_pair("12", "123"));
		m9.insert(std::make_pair("123", "12")); mp9.insert(ft::make_pair("123", "12"));
	}
};

void map_less_than_test() {
	std::vector<int> result, result2;
	MapBoolTest mt;

	result.push_back(mt.m1 < mt.m1); result.push_back(mt.m3 < mt.m3); result.push_back(mt.m5 < mt.m9);
	result.push_back(mt.m1 < mt.m2); result.push_back(mt.m3 < mt.m4); result.push_back(mt.m6 < mt.m6);
	result.push_back(mt.m1 < mt.m3); result.push_back(mt.m4 < mt.m4); result.push_back(mt.m6 < mt.m7);
	result.push_back(mt.m1 < mt.m4); result.push_back(mt.m5 < mt.m5); result.push_back(mt.m6 < mt.m8);
	result.push_back(mt.m2 < mt.m2); result.push_back(mt.m5 < mt.m6); result.push_back(mt.m6 < mt.m9);
	result.push_back(mt.m2 < mt.m3); result.push_back(mt.m5 < mt.m7); result.push_back(mt.m7 < mt.m7);
	result.push_back(mt.m2 < mt.m4); result.push_back(mt.m5 < mt.m8); result.push_back(mt.m7 < mt.m8);
	result.push_back(mt.m7 < mt.m9); result.push_back(mt.m8 < mt.m8); result.push_back(mt.m8 < mt.m9);
	result.push_back(mt.m9 < mt.m9);

	result2.push_back(mt.mp1 < mt.mp1); result2.push_back(mt.mp3 < mt.mp3); result2.push_back(mt.mp5 < mt.mp9);
	result2.push_back(mt.mp1 < mt.mp2); result2.push_back(mt.mp3 < mt.mp4); result2.push_back(mt.mp6 < mt.mp6);
	result2.push_back(mt.mp1 < mt.mp3); result2.push_back(mt.mp4 < mt.mp4); result2.push_back(mt.mp6 < mt.mp7);
	result2.push_back(mt.mp1 < mt.mp4); result2.push_back(mt.mp5 < mt.mp5); result2.push_back(mt.mp6 < mt.mp8);
	result2.push_back(mt.mp2 < mt.mp2); result2.push_back(mt.mp5 < mt.mp6); result2.push_back(mt.mp6 < mt.mp9);
	result2.push_back(mt.mp2 < mt.mp3); result2.push_back(mt.mp5 < mt.mp7); result2.push_back(mt.mp7 < mt.mp7);
	result2.push_back(mt.mp2 < mt.mp4); result2.push_back(mt.mp5 < mt.mp8); result2.push_back(mt.mp7 < mt.mp8);
	result2.push_back(mt.mp7 < mt.mp9); result2.push_back(mt.mp8 < mt.mp8); result2.push_back(mt.mp8 < mt.mp9);
	result2.push_back(mt.mp9 < mt.mp9);

	int i = 1;
	for ( std::vector<int>::iterator it = result.begin(), it2 = result2.begin(); it != result.end() ; ++it, ++it2, ++i )
		std::cout << i << ". Orig: " << *it << " \tFT: " << *it2 << std::endl;
}


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
	dict2.erase( 19 );
	for ( it = dict2.begin(); it != dict2.end(); ++it )
		std::cout << it->first << " ";

	std::cout << std::endl;
	std::cout << "Lower Bound:\t" << dict2.lower_bound( LOWERBOUND )->first << std::endl;
	std::cout << "Upper Bound:\t" << dict2.upper_bound( UPPERBOUND )->first << std::endl;
	std::cout << "Begin:\t\t" << dict2.begin()->first << std::endl;
	std::cout << "Size:\t\t" << dict2.size() << std::endl;
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
	dict.erase( 19 );
	for ( it = dict.begin(); it != dict.end(); ++it )
		std::cout << it->first << " ";

	std::cout << std::endl;
	std::cout << "Lower Bound:\t" << dict.lower_bound( LOWERBOUND )->first << std::endl;
	std::cout << "Upper Bound:\t" << dict.upper_bound( UPPERBOUND )->first << std::endl;
	std::cout << "Begin:\t\t" << dict.begin()->first << std::endl;
	std::cout << "Size:\t\t" << dict.size() << std::endl;
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

	std::map<int, int>::reverse_iterator	rit_orig = orig.rbegin();
	ft::map<int, int>::reverse_iterator		rit_ft = dict.rbegin();

	for ( ; rit_ft != dict.rend(); ++rit_ft, ++rit_orig )
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
	++rit; ++rito;
	--rit2; --rito2;
	std::cout << "Orig: " << rito->first << " \tFT: " << rit->first << std::endl;
	std::cout << "Orig: " << rito2->first << " \tFT: " << rit2->first << std::endl;

}

// void	compare( void ) {
// 	std::cout << "std::greater: " << std::plus<int>{}( 5, 5 ) << std::endl;
// 	std::cout << "------> std::plus <------" << std::endl;
// 	{
// 		std::map<int, int, std::plus<int> >	orig;
// 		ft::map<int, int, std::plus<int> >	dict;

// 		std::map<int, int>	data = makeRandomMap();

// 		orig.insert( data.begin(), data.end() );
// 		dict.insert( data.begin(), data.end() );

// 		std::map<int, int>::iterator	it_orig = orig.begin();
// 		ft::map<int, int>::iterator		it_ft = dict.begin();

// 		for ( ; it_ft != dict.end(); ++it_orig, ++it_ft )
// 			std::cout << "Orig: " << it_orig->first << " \tFT: " << it_ft->first << std::endl;
// 	}
// 	std::cout << "------> std::greater <------" << std::endl;
// 	{
// 		std::map<int, int, std::greater<int> >	orig;
// 		ft::map<int, int, std::greater<int> >	dict;

// 		std::map<int, int>	data = makeRandomMap();

// 		orig.insert( data.begin(), data.end() );
// 		dict.insert( data.begin(), data.end() );

// 		std::map<int, int>::iterator	it_orig = orig.begin();
// 		ft::map<int, int>::iterator		it_ft = dict.begin();

// 		for ( ; it_ft != dict.end(); ++it_orig, ++it_ft )
// 			std::cout << "Orig: " << it_orig->first << " \tFT: " << it_ft->first << std::endl;
// 	}
// }

void	insertTest( void ) {
	std::vector<int>	v1;
	std::vector<int>	v2;
	std::map<int, int>	mp1;
	ft::map<int, int>	mp2;
	std::pair<std::map<int, int>::iterator, bool>	pair1 = mp1.insert( std::make_pair( 7, 7 ) );
	ft::pair< ft::map<int, int>::iterator, bool> 	pair2 = mp2.insert( ft::make_pair( 7, 7 ) );

	std::map<int, int>::iterator	it1 = mp1.begin();
	ft::map<int, int>::iterator		it2 = mp2.begin();

	v1.push_back( it1->first );
	v1.push_back( it1->second );
	v1.push_back( pair1.first->first );
	v1.push_back( pair1.first->second );
	v1.push_back( pair1.second );

	v2.push_back( it2->first );
	v2.push_back( it2->second );
	v2.push_back( pair2.first->first );
	v2.push_back( pair2.first->second );
	v2.push_back( pair2.second );

	mp1.insert( std::make_pair( 9, 9 ) );
	std::pair< std::map<int, int>::iterator, bool >	pair3 = mp1.insert( std::make_pair( 9, 9 ) );
	std::map<int, int>::iterator	it3 = pair1.first;
	
	mp2.insert( ft::make_pair( 9, 9 ) );
	ft::pair< ft::map<int, int>::iterator, bool >	pair4 = mp2.insert( ft::make_pair( 9, 9 ) );
	ft::map<int, int>::iterator		it4 = pair2.first;

	std::cout << "Orig: " << pair3.first->first << " FT: " << pair4.first->first << std::endl;

	v1.push_back( it3->first );
	v1.push_back( it3->second );
	v1.push_back( pair3.first->first );
	v1.push_back( pair3.first->second );
	v1.push_back( pair3.second );

	v2.push_back( it4->first );
	v2.push_back( it4->second );
	v2.push_back( pair4.first->first );
	v2.push_back( pair4.first->second );
	v2.push_back( pair4.second );

	// for ( int i = 0, j = 0; i < 500000; ++i, ++j ) {
	// 	mp1.insert( std::make_pair( i, j ) );
	// 	mp2.insert( ft::make_pair( i, j ) );
	// }

	// std::map<int, int>::iterator	ito = mp1.begin();
	// ft::map<int, int>::iterator	itf = mp2.begin();
	// for ( ; ito != mp1.end(); ++ito, ++itf ) {
	// 	v1.push_back( ito->first );
	// 	v1.push_back( ito->second );
	// 	v2.push_back( itf->first );
	// 	v2.push_back( itf->second );
	// }

	v1.push_back( mp1.size() );
	v2.push_back( mp2.size() );

	std::vector<int>::iterator	itv1 = v1.begin();
	std::vector<int>::iterator	itv2 = v2.begin();
	for ( int i = 0; itv1 != v1.end(); ++itv1, ++itv2, ++i ) {
		if ( *itv1 != *itv2 )
			std::cout << "Error: " << i << " ";
		std::cout << "Value orig: " << *itv1 << " Value ft: " << *itv2 << std::endl;
	}
	
}


void	eraseTest( void ) {
	ft::map<int, int>	mp;
	std::vector<int>	v;
	std::map<int, int>	mp2;
	std::vector<int>	v2;

	v.push_back( mp.erase( 3 ) );
	v2.push_back( mp2.erase( 3 ) );
	for ( int i = 0, j = 0; i < 300000; ++i, ++j ) {
		mp.insert( ft::make_pair( i, j ) );
		mp2.insert( std::make_pair( i, j ) );
	}
	
	ft::map<int, int>::iterator		it = mp.begin();
	std::map<int, int>::iterator	it2 = mp2.begin();

	v.push_back( it->first );
	v.push_back( mp.erase( -5 ) );
	v.push_back( mp.size() );
	v.push_back( mp.erase( 0 ) );
	v.push_back( mp.size() );
	it = mp.begin();
	v.push_back( it->first );

	v2.push_back( it2->first );
	v2.push_back( mp2.erase( -5 ) );
	v2.push_back( mp2.size() );
	v2.push_back( mp2.erase( 0 ) );
	v2.push_back( mp2.size() );
	it2 = mp2.begin();
	v2.push_back( it2->first );

	ft::map<int, int>::iterator		it3 = mp.begin();
	std::map<int, int>::iterator	it4 = mp2.begin();

	for ( ; it3 != mp.end(); it3 = mp.begin() )
		mp.erase( it3->first );

	for ( ; it4 != mp2.end(); it4 = mp2.begin() )
		mp.erase( it4->first );

	ft::map<int, int>::iterator		end = mp.end();
	std::map<int, int>::iterator	end2 = mp2.end();

	--end; --end2;

	v.push_back( mp.erase( 299999 ) );
	v2.push_back( mp2.erase( 299999 ) );
	v.push_back( mp.size() );
	v2.push_back( mp2.size() );

	ft::map<int, int>	mp3;
	std::map<int, int>	mp4;

	for ( int i = 0, j = 0; i < 10; ++i, ++j ) {
		mp3.insert( ft::make_pair( i, j ) );
		mp4.insert( std::make_pair( i, j ) );
	}

	mp3.erase( 2 ); mp3.erase( 7 );
	mp4.erase( 2 ); mp4.erase( 7 );

	ft::map<int, int>::iterator		it5 = mp3.begin();
	std::map<int, int>::iterator	it6 = mp4.begin();

	for ( ; it5 != mp3.end(); ++it5, ++it6 ) {
		v.push_back( it5->first );
		v.push_back( it5->second );
		v2.push_back( it6->first );
		v2.push_back( it6->second );
	}

	std::vector<int>::iterator	itv1 = v.begin();
	std::vector<int>::iterator	itv2 = v2.begin();

	int i = 0;
	for ( ; itv1 != v.end(); ++itv1, ++itv2 ) {
		if ( *itv1 != *itv2 )
			++i;
	}
	std::cout << "Errors: " << i << std::endl;
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
	// std::cout << "----------- Compare -------------" << std::endl;
	// compare();
	std::cout << "----------- Insert Value -------------" << std::endl;
	insertTest();
	std::cout << "----------- Erase -------------" << std::endl;
	eraseTest();
	std::cout << "---------------------------------" << std::endl;
	map_less_than_test();
	// constructorTest();
	
	return 0;
}
