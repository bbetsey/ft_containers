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


		private:

			allocator_type		_alloc;
			node_type			_root;


			// MARK: - Class Methods (private)

			bool	equal( const node_type &lhs, const node_type &rhs )	{ return lhs == rhs; }
			
			void	colorToggle( node_type &node ) {
				node.color = ( node.color == RED )
					? BLACK
					: RED
			}

			node_type	*getFather( node_type *node ) { return node->parent; }
			
			node_type	*getGrandfather( node_type *node ) {
				if (  getFather( node ) )
					return getFather( node->parent );
				return NULL;
			}

			node_type	*getBrother( node_type *node ) {
				if ( getFather( node ) )
					return getFather( node )->right == node ? getFather( node )->left : getFather( node )->right;
				return NULL;
			}

			node_type	*getUncle( node_type *node ) {
				if ( getGrandfather( node ) )
					return getBrother( getFather( node ) );
				return NULL;
			}


		public:


			// MARK: - Getters

			node_type		*getRoot( void )		{ return _root; }
			allocator_type	getAllocator( void )	{ return _alloc; }

			
		
	};


}

#endif
