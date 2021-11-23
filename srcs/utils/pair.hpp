#ifndef PAIR_HPP
# define PAIR_HPP

# include <iostream>

namespace ft {

	template < class T1, class T2 >
	struct pair {
		
		
		// MARK: - Member Types

		typedef T1	first_type;
		typedef T2	second_type;

		
		// MARK: - Member Objects

		first_type	first;
		second_type	second;

		
		// MARK: - Struct Constructor

		pair( void ) : first(), second() {}

		pair( const T1 &x, const T2 &y ) : first( x ), second( y ) {}

		
		// MARK: - Struct Copy Constructor

		template < class U1, class U2 >
		pair( const pair<U1, U2> &p ) : first( p.first ), second( p.second ) {}

		
		// MARK: - Struct Assignation Overload

		pair	&operator = ( const pair &src ) {
			if ( this != &src ) {
				first = src.first;
				second = src.second;
			}
			return *this;
		}

		// MARK: - Member functions

		void	swap( pair &src ) {
			std::swap( first, src.first );
			std::swap( second, src.second );
		}

	};


	// MARK: - Non Member Functions

	template < class T1, class T2 >
	pair<T1, T2>	make_pair( T1 t, T2 u ) {
		return pair<T1, T2>( t, u );
	}

	template < class T1, class T2 >
	bool	operator == ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template < class T1, class T2 >
	bool	operator != ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return !(lhs == rhs);
	}

	template < class T1, class T2 >
	bool	operator < ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return lhs.first < rhs.first || !( lhs.first < lhs.second ) && lhs.second < rhs.second;
	}

	template < class T1, class T2 >
	bool	operator <= ( const pair<T2, T2> &lhs, const pair<T1, T2> &rhs ) {
		return !( rhs < lhs );
	}

	template < class T1, class T2 >
	bool	operator > ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return rhs < lhs;
	}

	template < class T1, class T2 >
	bool	operator >= ( const pair<T1, T2> &lhs, const pair<T1, T2> &rhs ) {
		return !( lhs < rhs );
	}

}



#endif
