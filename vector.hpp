#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "utils/utils.hpp"
# include "utils/random_access_iterator.hpp"
# include "utils/type_traits.hpp"

namespace ft {

	template < typename T, class Alloc = std::allocator<T> >
	class vector {

		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;

			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_type		difference_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;

		private:
			allocator_type	alloc;
			pointer			start;
			pointer			end;
			size_type		size;
			size_type		capacity;

		public:

			//MARK: - Class Default Constructor

			explicit vector( allocator_type &alloc = allocator_type() )
			:
				alloc( alloc ),
				start( NULL ),
				end( NULL ),
				size( 0 );
				capacity( 0 );
			{}

			//MARK: - Class Constructor ( with default value )

			explicit vector( size_type count, const value_type &value = value_type(),
								allocator_type &alloc = allocator_type() )
			:
				alloc( alloc ),
				start( NULL ),
				end( NULL ),
				size( count );
				capacity( count );
			{
				start = alloc.allocate( count );
				end = start + count;
				for (size_type i = 0; i < count, i++)
					alloc.construct( start + i, value );
			}

			//MARK: - Class Constructor ( with value )

			explicit vector( size_type count, const value_type &value,
							allocator_type &alloc = allocator_type() )
			:
				alloc( alloc ),
				start( NULL ),
				end( NULL ),
				size( count );
				capacity( count );
			{
				start = alloc.allocate( count );
				end = start + count;
				for (size_type i = 0; i < count, i++)
					alloc.construct( start + i, value );
			}

			//MARK: - Class Constructor ( with range )


	};


};

	 
#endif
