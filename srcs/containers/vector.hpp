#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "../iterators/random_access_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utils/lexicographical_compare.hpp"

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector {

		public:

			//MARK: - Member types

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
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const iterator>			const_reverse_iterator;
		

		private:

			allocator_type	_alloc;
			pointer			_start;
			size_type		_size;
			size_type		_capacity;

		
		public:

			//MARK: - Class Constructor

			explicit vector( const allocator_type &alloc = allocator_type() );

			explicit vector( size_type count,
							 const value_type &value = value_type(),
							 const allocator_type &alloc = allocator_type() );

			template < class InputIterator >
			vector( InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type() );		


			//MARK: - Class Copy Constructor

			vector( const vector &src );


			//MARK: - Class Assignation Overload

			vector	&operator = ( const vector &src );


			//MARK: - Class Distructor

			~vector( void );


			//MARK: - Class Methods ( getters )

			allocator_type	get_allocator( void ) const;


			//MARK: - Class Methods

			void	assign( size_type count, const value_type &value );

			template < class InputIterator >
			void	assign( InputIterator first, InputIterator last );


			//MARK: - Class Element Access
			
			reference			at( size_type pos );
			const_reference		at( size_type pos ) const;

			reference			operator [] ( size_type pos );
			const_reference		operator [] ( size_type pos ) const;

			reference			front( void );
			const_reference		front( void ) const;

			reference			back( void );
			const_reference		back( void ) const;

			value_type			*data( void );
			const value_type	*data( void ) const;


			//MARK: - Iterators

			iterator				begin( void );
			const_iterator			begin( void ) const;

			iterator				end( void );
			const_iterator			end( void ) const;

			reverse_iterator		rbegin( void );
			const_reverse_iterator	rbegin( void ) const;

			reverse_iterator		rend( void );
			const_reverse_iterator	rend( void ) const;


			//MARK: - Capacity

			bool		empty( void ) const;
			size_type	size( void ) const;
			size_type	max_size( void ) const;
			void		reserve( size_type new_cap );
			size_type	capacity( void ) const;


			//MARK: - Modifiers

			void		clear( void );
			iterator	insert( iterator pos, const value_type &value );
			void		insert( iterator pos, size_type count, const value_type &value );

			template < class InputIterator >
			void		insert( iterator pos, InputIterator first, InputIterator last );

			iterator	erase( iterator pos );
			iterator	erase( iterator first, iterator last );

			void		push_back( const value_type &value );
			void		pop_back( void );
			void		resize( size_type count, value_type value = value_type() );
			void		swap( vector &src );

	};


	//MARK: - Not Member Functions

	template < class T, class Alloc >
	bool	operator == ( const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs ) {
		if (lhs.size() != rhs.size())
			return false;

		typename ft::vector<T>::iterator it_lhs = lhs.begin();
		typename ft::vector<T>::iterator it_rhs = rhs.begin();

		for (; it_lhs != lhs.end(); ++it_lhs, ++it_rhs)
			if (*it_lhs != *it_rhs)
				return false;

		return true;
	}

	template < class T, class Alloc >
	bool	operator != ( const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs ) {
		return !(lhs == rhs);
	}

	template < class T, class Alloc >
	bool	operator > ( const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs ) {
		return !ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}

	template < class T, class Alloc >
	bool	operator >= ( const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs ) {
		if (rhs == lhs)
			return true;
		return !ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}

	template < class T, class Alloc >
	bool	operator < ( const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs ) {
		return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}

	template < class T, class Alloc >
	bool	operator <= ( const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs ) {
		if (rhs == lhs)
			return true;
		return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}

	template < class T, class Alloc >
	void	swap( ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs ) {
		lhs.swap( rhs );
	}

}


#endif
