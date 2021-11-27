#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>

namespace ft {

	enum colors {
		RED,
		BlACK
	};

	template < class T, class Compare >
	struct node {

		// MARK: - Member Types

		typedef T			value_type;
		typedef Compare		compare_type;


		// MARK: - Member Values

		value_type	value;
		colors		color;
		node		*parent;
		node		*left;
		node		*right;


		// MARK: - Struct Constructors

		node( void ) : value(), color( RED ), parent( nullptr ), left( nullptr ), right( nullptr ) {}

		node( node *parent = nullptr, node *left = nullptr, node *right = nullptr )
		:
			value(),
			color( RED ),
			parent( parent ),
			left( left ),
			right( right )
		{}

		node( const value_type &val, node *parent = nullptr, node *left = nullptr, node *right = nullptr )
		:
			value( val ),
			color( RED ),
			parent( parent ),
			left( left ),
			right( right )
		{}


		// MARK: - Struct Copy Constructor

		node( const node &src ) : value( src.value ), color( src.color ), parent( src.parent ), left( src.left ), right( src.right ) {}


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
			return !compare_type{}( value, src.value ) && !compare_type{}( src.value, value );
		}

		bool	operator < ( const node &src ) {
			return compare_type{}( value, src.value );
		}

		
		// MARK: - Member Functions

		void	colorToggle( void ) {
			color = ( color == RED )
				? BlACK
				: RED;
		}

		bool	isOnTheLeftSide( void ) {
			if ( parent )
				return this == parent->left;
			return false;
		}

		bool	hasRedChild( void ) {
			return ( right && right->color == RED ) || ( left && left->color == RED );
		}

		node	*getFather( void ) {
			return parent;
		}

		node	*getGrandfather( void ) {
			if ( parent )
				return getFather( parent );
			return NULL;
		}

		node	*getBrother( void ) {
			if ( parent )
				return isOnTheLeftSide() ? parent->right : parent->left;
			return NULL;
		}

		node	*getUncle( void ) {
			if ( getGrandfather() )
				return getBrother( parent );
			return NULL;
		}

	};

}

#endif
