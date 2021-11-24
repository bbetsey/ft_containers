#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> >
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
			

	}

}

#endif
