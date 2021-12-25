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
			typedef size_t					size_type;
			typedef ft::node<value_type>	node_type;
			typedef rbTree<value_type>		tree_type;


		private:

			node_type*		_root;
			node_type		_leaf;
			size_type		_size;


			// MARK: - Class Methods (private)

			bool	equal( const node_type &lhs, const node_type &rhs ) {
				return !_comp( lhs.value, rhs.value ) && !_comp( lhs.value, rhs.value );
			}

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


			// -------------------- INSERT MODE --------------------

			void	insertCase1( node_type *node ) {
				if ( node->parent == NULL )
					node->color = BLACK;
				else
					insertCase2( node );
			}

			void	insertCase2( node_type *node ) {
				if ( node->parent->color == BLACK )
					return;
				else
					insertCase3( node );
			}

			void	insertCase3( node_type *node ) {
				node_type	*u = node->getUncle();
				node_type	*g;

				if ( u  && u->color == RED ) {
					node->parent->color = BLACK;
					u->color = BLACK;
					g = node->getGrandfather();
					g->color = RED;
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

				node->parent->color = BLACK;
				g->color = RED;
				if ( node->isOnTheLeftSide() && node->parent == g->left ) {
					rightRotate( g );
				} else {
					leftRotate( g );
				}
			}


			// -------------------- DELETE MODE --------------------

			void	replaceNode( node_type *node, node_type *child ) {
				child->parent = node->parent;
				if ( node->isOnTheLeftSide() )
					node->parent->left = child;
				else
					node->parent->right = child;
			}

			void	deleteOneChild( node_type *node ) {
				node_type *child = node->right->isLeaf ? node->left : node->right;

				replaceNode( node, child );
				if ( node->color == BLACK ) {
					if ( child->color == RED )
						child->color = BLACK;
					else
						deleteCase1( child );
				}
			}

			void	deleteCase1( node_type *node ) {
				if ( node->parent )
					deleteCase2( node );
			}

			void	deleteCase2( node_type *node ) {
				node_type *brother = node->getBrother();

				if ( brother->color == RED ) {
					node->parent->color = RED;
					brother->color = BLACK;
					if ( node->isOnTheLeftSide() )
						leftRotate( node->parent );
					else
						rightRotate( node->parent );
				}
				deleteCase3( node );
			}

			void	deleteCase3( node_type *node ) {
				node_type *brother = node->getBrother();

				if ( node->parent->color == BLACK && brother->color == BLACK && brother->right->color == BLACK && brother->left->color == BLACK ) {
					brother->color = RED;
					deleteCase1( node->parent );
				} else
					deleteCase4( node );
			}

			void	deleteCase4( node_type *node ) {
				node_type *brother = node->getBrother();

				if ( node->parent->color == RED && brother->color == BLACK && brother->right->color == BLACK && brother->left->color == BLACK ) {
					brother->color = RED;
					node->parent->color = BLACK;
				} else
					deleteCase5( node );
			}

			void	deleteCase5( node_type *node ) {
				node_type *brother = node->getBrother();

				if ( brother->color == BLACK ) {
					if ( node->isOnTheLeftSide() && brother->right->color == BLACK && brother->left->color == RED ) {
						brother->color = RED;
						brother->left->color = BLACK;
						rightRotate( brother );
					} else if ( !node->isOnTheLeftSide() && brother->left->color == BLACK && brother->right->color == RED ) {
						brother->color = RED;
						brother->right->color = BLACK;
						leftRotate( brother );
					}
				}
				deleteCase6( node );
			}

			void	deleteCase6( node_type *node ) {
				node_type *brother = node->getBrother();

				brother->color = node->parent->color;
				node->parent->color = BLACK;
				
				if ( node->isOnTheLeftSide() ) {
					brother->right->color = BLACK;
					leftRotate( node->parent );
				} else {
					brother->left->color = BLACK;
					rightRotate( node->parent );
				}
			}


		public:


			// MARK: - Class Constructors

			rbTree( void ) : _size( 0 ) {
				_leaf.left = &_leaf;
				_leaf.right = &_leaf;
				_leaf.parent = &_leaf;
				_leaf.isLeaf = true;
				_leaf.color = BLACK;
				_root = &_leaf;
			}


			// MARK: - Class Copy Constructor

			rbTree( const tree_type &src ) : _size( src._size ), _leaf( src._leaf ), _root( src._root ) {}

			
			// MARK: - Class Assignation Overload

			rbTree	&operator = ( const tree_type &src ) {
				if ( this != &src ) {
					_leaf = src._leaf;
					_size = src._size;
					_root = src._root;
				}
				return *this;
			}


			// MARK: - Class Distructor

			~rbTree( void ) {}


			// MARK: - Getters

			node_type		*root( void )		{ return _root; }
			node_type		*leaf( void )		{ return &_leaf; }
			size_type		size( void )		{ return _size; }


			// MARK: - Setters

			void	setRoot( node_type *root )		{ _root = root; }
			void	setSize( size_type new_size )	{ _size = new_size; }
			void	sizeUp( void )					{ ++_size; }
			void	sizeDown( void )				{ --_size; }


			// MARK: - Class Methods
			
			void	insertCheck( node_type *node )	{ insertCase1( node ); }
			void	deleteCheck( node_type *node )	{ deleteOneChild( node ); }

			// node_type	*begin( void )	{ return _smallest; }
			// node_type	*last( void )	{ return _biggest; }
			// node_type	*end( void )	{ _biggest->right->value = _smallest->value; return _biggest->right; }

			node_type	*begin( void ) {
				node_type *tmp = _root;

				while ( !tmp->left->isLeaf )
					tmp = tmp->left;
				return tmp;
			}

			node_type	*last( void ) {
				node_type *tmp = _root;

				while ( !tmp->right->isLeaf )
					tmp = tmp->right;
				return tmp;
			}

			node_type	*end( void ) {
				return last()->right;
			}

			node_type	*findNodeWithOneLeafOrMore( node_type *node ) {
				if ( node->hasOneOrMoreLeaf() )
					return node;
				node = node->right;
				while ( !node->left->isLeaf )
					node = node->left;
				return node;
			}

	};

}

#endif
