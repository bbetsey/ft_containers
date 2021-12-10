#ifndef TREE_HPP
# define TREE_HPP

# include <iostream>
# include "pair.hpp"
# include "node.hpp"

namespace ft {

	template < class Value >
	class rbTree {

		public:

			// MARK: - Member Types

			typedef Value					value_type;
			typedef ft::node<value_type>	node_type;
			typedef size_t					size_type;


		private:

			node_type			*_root;
			size_type			_size;


			// MARK: - Class Methods (private)

			bool	equal( const node_type &lhs, const node_type &rhs )	{ return lhs == rhs; }

			void	leftRotate( node_type *node ) {
				node_type	*pivot = node->right;

				pivot->parent = node->parent;
				if ( node->parent ) {
					if ( node->isOnTheLeftSide() )
						node->parent->left = pivot;
					else
						node->parent->right = pivot;
				}
				node->right = pivot->left;
				if ( pivot->left )
					pivot->left->parent = node;
				node->parent = pivot;
				pivot->left = node;
				if ( node == _root ) _root = pivot;
			}

			void	rightRotate( node_type *node ) {
				node_type	*pivot = node->left;

				pivot->parent = node->parent;
				if ( node->parent ) {
					if ( node->isOnTheLeftSide() )
						node->parent->left = pivot;
					else
						node->parent->right = pivot;
				}
				node->left = pivot->right;
				if ( pivot->right )
					pivot->right->parent = node;
				node->parent = pivot;
				pivot->right = node;
				if ( node == _root ) _root = pivot;
			}

			void	insertCase1( node_type *node ) {
				if ( node->parent == NULL )
					node->color = colors.BLACK;
				else
					insertCase2( node );
			}

			void	insertCase2( node_type *node ) {
				if ( node->parent->color == colors.BLACK )
					return;
				else
					insertCase3( node );
			}

			void	insertCase3( node_type *node ) {
				node_type	*u = node->getUncle();
				node_type	*g;

				if ( u  && u->color == colors.RED ) {
					node->parent->color = colors.BLACK;
					u->color = BLACK;
					g = node->getGrandfather();
					g->color = colors.RED;
					insertCase1( g );
				} else {
					insertCase4( node );
				}
			}

			void	insertCase4( node_type *node ) {
				node_type	*g = node->getGrandfather();

				if ( !node->isOnTheLeftSide() && node->parent == g->left ) {
					leftRotate( node->parent );
					node = node->left;
				} else if ( node->isOnTheLeftSide() && node->parent == g->right ) {
					rightRotate( node->parent );
					node = node->right;
				}
				insertCase5( node );
			}

			void	insertCase5( node_type *node ) {
				node_type	*g = node->getGrandfather();

				node->parent->color = colors.BLACK;
				g->color = colors.RED;
				if ( node->isOnTheLeftSide() && node->parent == g->left ) {
					rightRotate( g );
				} else {
					leftRotate( g );
				}
			}


		public:

			// MARK: - Class Constructors

			tree( void ) : _size( 0 ), _root( nullptr ) {}


			// MARK: - Class Distructor

			~tree( void ) {}


			// MARK: - Getters

			node_type		*getRoot( void )		{ return _root; }


			// MARK: - Class Methods
			
			void	checkTheTree( node_type *node )	{ insertCase1( node ); }

			node_type	begin( void ) {
				node_type *tmp = _root;

				while ( !tmp->left->isLeaf )
					tmp = tmp->left;
				return tmp;
			}

			node_type	last( void ) {
				node_type *tmp = _root;

				while ( !tmp->right->isLeaf )
					tmp = tmp->right;
				return tmp;
			}

			node_type	end( void ) {
				node_type *tmp = _root;

				while ( !tmp->right->isLeaf )
					tmp = tmp->right;
				return tmp->right;
			}
		
	};

}

#endif
