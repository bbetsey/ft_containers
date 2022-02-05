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

			void	checkDelete( node_type *node ) {
				while ( node != _root && node->color == BLACK ) {
					if ( node->isOnTheLeftSide() ) {
						node_type *brother = node->parent->right;
						if ( brother->color == RED ) {
							brother->color = BLACK;
							node->parent->color = RED;
							leftRotate( node->parent );
							brother = node->parent->right;
						}
						if ( brother->left->color == BLACK && brother->right->color == BLACK ) {
							brother->color = RED;
							node = node->parent;
						} else {
							if ( brother->color == BLACK ) {
								brother->left->color = BLACK;
								brother->color = RED;
								rightRotate( brother );
								brother = node->parent->right;
							}
							brother->color = node->parent->color;
							node->parent->color = BLACK;
							brother->right->color = BLACK;
							leftRotate( node->parent );
							node = _root;
						}
					} else {
						node_type *brother = node->parent->left;
						if ( brother->color == RED ) {
							brother->color = BLACK;
							node->parent->color = RED;
							rightRotate( node->parent );
							brother = node->parent->left;
						}
						if ( brother->left->color == BLACK && brother->right->color == BLACK ) {
							brother->color = RED;
							node = node->parent;
						} else {
							if ( brother->color == BLACK ) {
								brother->left->color = BLACK;
								brother->color = RED;
								leftRotate( brother );
								brother = node->parent->left;
							}
							brother->color = node->parent->color;
							node->parent->color = BLACK;
							brother->right->color = BLACK;
							rightRotate( node->parent );
							node = _root;
						}
					}
				}
				node->color = BLACK;
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

			rbTree( const tree_type & ) : _size( 0 ) {
				_leaf.left = &_leaf;
				_leaf.right = &_leaf;
				_leaf.parent = &_leaf;
				_leaf.isLeaf = true;
				_leaf.color = BLACK;
				_root = &_leaf;
			}

			
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

			void	setRoot( node_type *root )		{ _root = root; _leaf.left = _root; _leaf.right = _root; }
			void	setSize( size_type new_size )	{ _size = new_size; }
			void	sizeUp( void )					{ ++_size; }
			void	sizeDown( void )				{ --_size; }


			// MARK: - Class Methods
			
			void	insertCheck( node_type *node )	{ insertCase1( node ); }

			node_type	*getLast( void ) {
				node_type* tmp = _root;
				while (!tmp->right->isLeaf)
					tmp = tmp->right;
				return tmp;
			}

			node_type	*getBegin( void ) {
				node_type* tmp = _root;
				while (!tmp->left->isLeaf)
					tmp = tmp->left;
				return tmp;
			}

			node_type	*begin( void ) {
				return _leaf.left;
			}

			node_type	*last( void ) {
				return _leaf.right;
			}

			node_type	*end( void ) {
				return &_leaf;
			}

			node_type	*findNodeWithOneLeafOrMore( node_type *node ) {
				if ( node->hasOneOrMoreLeaf() )
					return node;
				node = node->right;
				while ( !node->left->isLeaf )
					node = node->left;
				return node;
			}

			void	nodeDelete( node_type *node ) {
				if ( !node || node->isLeaf ) return;
				
				node_type *tmp, *upperNode;
				upperNode = findNodeWithOneLeafOrMore( node );
				tmp = ( upperNode->left->isLeaf )
					? upperNode->right
					: upperNode->left;
				tmp->parent = upperNode->parent;
				if ( upperNode->parent ) {
					if ( upperNode->isOnTheLeftSide() )
						upperNode->parent->left = tmp;
					else
						upperNode->parent->right = tmp;
				} else {
					_root = tmp;
				}
				if ( upperNode != node ) {
					delete node->value;
					value_type *new_value = new value_type( *upperNode->value );
					node->value = new_value;
				}
				if ( upperNode->color == BLACK ) checkDelete( tmp );
				--_size;

				delete upperNode;

				if ( _size == 0 ) {
					_leaf.right = _root;
					_leaf.left = _root;
				} else {
					if ( _leaf.right == node )	_leaf.right = getLast();
					if ( _leaf.left == node )	_leaf.left = getBegin();
				}
			}

	};

}

#endif
