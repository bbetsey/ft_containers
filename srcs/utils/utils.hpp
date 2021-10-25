#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>


namespace ft {


	//MARK: - std::iterator

	template < class Category, class T, class Distance, class Pointer = T*, class Reference = T& >
	class iterator {
		public:
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	};


	//MARK: - Iterators Category Tags

	class input_iterator_tag {};
	class forward_iterator_tag {};
	class bidirectional_iterator_tag {};
	class random_access_iterator_tag {};

};

#endif
