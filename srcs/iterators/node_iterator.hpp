#ifndef NODE_ITERATOR_HPP
# define NODE_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "../utils/type_traits.hpp"


namespace ft {

	template < class Node, class Value >
	class node_iterator {

		public:

			typedef Node							iterator_type;
			typedef Value							value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef Value&							reference;
			typedef const Value&					const_reference;
			typedef Value*							pointer;
			typedef const Value*					const_pointer;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			

		private:

			iterator_type	node;

			void	next( void ) {
				if ( !node->right->isLeaf ) {
					node = node->right;
					while ( !node->left->isLeaf )
						node = node->left;
				} else {
					iterator_type	current = node;
					while ( node->parent && !node->isOnTheLeftSide() )
						node = node->parent;
					node = ( node->parent ) ? node->parent : current->right;
				}
			}

			void	prev( void ) {
				if ( node->isLeaf )
					node = node->parent;
				if ( !node->left->isLeaf ) {
					node = node->left;
					while ( !node->right->isLeaf )
						node = node->right;
				} else {
					iterator_type	current = node;
					node = node->parent;
					while ( node->parent && node->isOnTheLeftSide() )
						node = node->parent;
					node = ( node->parent ) ? node->parent : current->left;
				}
			}

		
		public:

			// MARK: - Class Constructor

			node_iterator( iterator_type node = nullptr ) : node( node ) {}


			// MARK: - Class Copy Constructor

			node_iterator( const node_iterator &src ) : node( src.node ) {}

			template < class N1, class V1 >
			node_iterator( const node_iterator<N1, V1> &src, typename ft::enable_if<std::is_convertible<N1, V1>::value>::type& = 0 ) : node( src.base() ) {}


			// MARK: - Class Assignation Overload

			node_iterator	&operator = ( const node_iterator &src ) {
				if ( this != &src )
					node = src.node;
				return *this;
			}


			// MARK: - Class Distructor

			~node_iterator( void ) {}


			// MARK - Class Methods

			iterator_type	base( void ) const			{ return node; }

			node_iterator	&operator ++ ( void )		{ next(); return *this; }
			node_iterator	operator ++ ( int )			{ node_iterator tmp( *this ); next(); return tmp; }

			node_iterator	&operator -- ( void )		{ prev(); return *this; }
			node_iterator	operator -- ( int )			{ node_iterator tmp( *this ); prev(); return tmp; }

			reference		operator * ( void )			{ return *(node->value); }
			const_reference	operator * ( void ) const	{ return *(node->value); }
			pointer			operator -> ( void )		{ return std::addressof( *(node->value) ); }
			const_pointer	operator -> ( void ) const	{ return std::addressof( *(node->value) ); }

			bool			operator == ( const node_iterator &src ) const	{ return node == src.node; }
			bool			operator != ( const node_iterator &src ) const	{ return node != src.node; }
			bool			operator > ( const node_iterator &src ) const	{ return node->value > src.node->value; }
			bool			operator < ( const node_iterator &src ) const	{ return node->value < src.node->value; }
			bool			operator >= ( const node_iterator &src ) const	{ return node->value >= src.node->value; }
			bool			operator <= ( const node_iterator &src ) const	{ return node->value <= src.node->value; }

	};

}



#endif
