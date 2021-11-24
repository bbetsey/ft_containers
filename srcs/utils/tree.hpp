#ifndef TREE_HPP
# define TREE_HPP

# include <iostream>
# include "pair.hpp"

namespace ft {

	template < class Node, class T, class Compare, class Alloc = std::allocator<Node> >
	class rbTree {

		public:

			// MARK: - Member Types

			typedef Node			node_type;
			typedef T				value_type;
			typedef Compare			compare_type;
			typedef Alloc			allocator_type;


		private:

			allocator_type		_alloc;
			compare_type		_compare;
			node_type			_root;


		public:

			
		
	};


}

#endif
