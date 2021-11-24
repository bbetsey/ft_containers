#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "../utils/pair.hpp"

namespace ft {

	template < class Key, class Value >
	struct mapPairCmp {

		typedef bool					result_type;
		typedef pair<const Key, Value>	argument_type;

		bool	operator () ( const argument_type &lhs, const argument_type &rhs ) {
			return lhs.first < rhs.second;
		}
		
	};

	template < class Key, class T, class Compare = ft::mapPairCmp<Key, T>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map {

		public:

			// MARK: - Member Types

			typedef Key									key_type;
			typedef T									mapped_type;
			typedef typename ft::pair<const Key, T>		value_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef Compare								key_compare;
			typedef Allocator							allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			

	};

}

#endif
