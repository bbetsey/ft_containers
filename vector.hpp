#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>


namespace ft {

	template < typename T, class Alloc = std::allocator<T> >
	class vector {

		public:
			typedef T			value_type;
			typedef Alloc		allocator_type;
			typedef size_t		size_type;
			typedef long int	difference_type;

			typedef &T			reference;

		private:


	}


}


#endif
