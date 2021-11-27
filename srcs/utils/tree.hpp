#ifndef TREE_HPP
# define TREE_HPP

# include <iostream>
# include "pair.hpp"
# include "node.hpp"

namespace ft {

	template < class Node, class Alloc = std::allocator<Node> >
	class rbTree {

		public:

			// MARK: - Member Types

			typedef Node			node_type;
			typedef Alloc			allocator_type;
			typedef size_t			size_type;


		private:

			allocator_type		_alloc;
			node_type			_root;
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

			void	freeTree( node_type *node ) {
				if ( node ) {
					freeTree( node->left );
					freeTree( node->right );
					_alloc.destroy( node );
					_alloc.deallocate( node, 1 );
				}
			}


		public:


			// MARK: - Getters

			node_type		*getRoot( void )		{ return _root; }
			allocator_type	getAllocator( void )	{ return _alloc; }


			// MARK: - Class Constructors

			tree( void ) : _alloc( allocator_type() ), _size( 0 ) {
				node_type	node;
				_root = _alloc.allocate( 1 );
				*_root = node;
				_root->color = colors.BLACK;
			}


			// MARK: - Class Distructor

			~tree( void ) {
				freeTree( _root );
			}
		
	};


}

#endif
