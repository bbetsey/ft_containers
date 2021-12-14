#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>

namespace ft {

	enum colors {
		RED,
		BLACK
	};

	template < class Value >
	struct node {

		// MARK: - Member Types

		typedef Value		value_type;
		typedef node<Value>	node_type;


		// MARK: - Member Values

		value_type	*value;
		colors		color;
		bool		isLeaf;
		node		*parent;
		node		*left;
		node		*right;


		// MARK: - Struct Constructors

		node( void ) : value( new value_type() ), color( BLACK ), isLeaf( true ), parent( nullptr ), left( nullptr ), right( nullptr ) {}

		node( const value_type &val, node *parent = nullptr, node *left = nullptr, node *right = nullptr )
		:
			value( new value_type(val) ),
			color( BLACK ),
			isLeaf( false ), 
			parent( parent ),
			left( left ),
			right( right )
		{}


		// MARK: - Struct Copy Constructor

		node( const node &src ) : value( src.value ), color( src.color ), isLeaf( src.isLeaf ), parent( src.parent ), left( src.left ), right( src.right ) {}


		// MARK: - Struct Distructor

		~node( void ) { if ( value ) delete value; }


		// MARK: - Struct Assignation Overload

		node	&operator = ( const node &src ) {
			if ( this != src ) {
				value = src.value;
				color = src.color;
				isLeaf = src.isLeaf;
				parent = src.parent;
				left = src.left;
				right = src.right;
			}
			return *this;
		}

		
		// MARK: - Member Functions

		void	colorToggle( void ) {
			color = ( color == RED ) ? BLACK : RED;
		}

		bool	isOnTheLeftSide( void ) const {
			if ( parent )
				return this == parent->left;
			return false;
		}

		bool	hasOneOrMoreLeaf( void ) {
			return left->isLeaf || right->isLeaf;
		}

		node	*getFather( void ) {
			return parent;
		}

		node	*getGrandfather( void ) {
			if ( parent && parent->parent )
				return parent->parent;
			return NULL;
		}

		node	*getBrother( void ) {
			if ( parent )
				return isOnTheLeftSide() ? parent->right : parent->left;
			return NULL;
		}

		node	*getBrother( node_type *node ) {
			if ( node->parent )
				return isOnTheLeftSide() ? node->parent->right : node->parent->left;
			return NULL;
		}

		node	*getUncle( void ) {
			if ( getGrandfather() )
				return getBrother( parent );
			return NULL;
		}

	};

	template < class T, class Compare >
	std::ostream	&operator << ( std::ostream &os, const ft::node<T> &src ) {
		if ( !src )
			os << "[none]";
		else { 
			if ( src.color == RED )
				os << "\033[0;31m";
			os << src.value << "\033[0m";
		}
		return os;
	}

}

#endif
