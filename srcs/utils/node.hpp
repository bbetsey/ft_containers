#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>

namespace ft {

	template < class T >
	struct node {

		// MARK: - Member Types

		typedef T	value_type;


		// MARK: - Member Values

		value_type	value;
		node		*parent;
		node		*left;
		node		*right;


		// MARK: - Struct Constructors

		node( void ) : value(), parent( nullptr ), left( nullptr ), right( nullptr ) {}

		node( node *parent = nullptr, node *left = nullptr, node *right = nullptr )
		:
			value(),
			parent( parent ),
			left( left ),
			right( right )
		{}

		node( const value_type &val, node *parent = nullptr, node *left = nullptr, node *right = nullptr )
		:
			value( val ),
			parent( parent ),
			left( left ),
			right( right )
		{}


		// MARK: - Struct Copy Constructor

		node( const node &src ) : value( src.value ), parent( src.parent ), left( src.left ), right( src.right ) {}


		// MARK: - Struct Distructor

		~node( void ) {}


		// MARK: - Struct Assignation Overload

		node	&operator = ( const node &src ) {
			if ( this != src ) {
				value = src.value;
				parent = src.parent;
				left = src.left;
				right = src.right;
			}
			return *this;
		}


		// MARK: - Member Bool Overloads

		bool	operator == ( const node &src ) {
			if ( value == src.value )
				return true;
			return false;
		}
		
	};

}

#endif
