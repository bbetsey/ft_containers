#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "../iterators/random_access_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utils/lexicographical_compare.hpp"
# include "../utils/type_traits.hpp"

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

			allocator_type		_alloc;
			pointer				_start;
			size_type			_size;
			size_type			_capacity;

		
		public:


			//MARK: - Class Constructors ✓

			explicit vector( const allocator_type &alloc = allocator_type() );

			explicit vector( size_type count,
							 const value_type &value = value_type(),
							 const allocator_type &alloc = allocator_type() );

			template < class InputIterator >
			vector( InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0 );



			//MARK: - Class Copy Constructor ✓

			vector( const vector &src )
			:
				_alloc( src.alloc ),
				_start( NULL ),
				_size( src._size ),
				_capacity( src._capacity )
			{
				insert( begin(), src.begin(), src.end() );
			}



			//MARK: - Class Assignation Overload ✓

			vector	&operator = ( const vector &src ) {
				if (this != &src) {
					clear();
					insert( begin(), src.begin(), src.end() );
				}
				return *this;
			}



			//MARK: - Class Distructor ✓

			~vector( void ) {
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy( &(*it) );
				_alloc.deallocate( _start, _capacity );
			}



			//MARK: - Class Methods ( getters ) ✓

			allocator_type	get_allocator( void ) const {
				return _alloc;
			}



			//MARK: - Class Methods ✓

			void	assign( size_type count, const value_type &value ) {
				clear();
				_size = count;
				if (count > _capacity) {
					_alloc.deallocate( _start, _capacity );
					_capacity = _size;
					_start = _alloc.allocate( _capacity );
				}
				for (iterator it = begin(); it != end(); ++it)
					_alloc.construct( it.operator->() , value );
			}

			template < class InputIterator >
			void	assign( InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0 ) {
				clear();
				for (InputIterator it = first; it != last; ++it)
					++_size;
				if ( _size > _capacity ) {
					_alloc.deallocate( _start, _capacity );
					_capacity = _size;
					_start = _alloc.allocate( _capacity );
				}
				for (iterator it = begin(); first != last; ++it, ++first)
					_alloc.construct( it.operator->(), *first );
			}



			//MARK: - Class Element Access

			reference			at( size_type pos ) {
				if (pos > _size)
					throw std::out_of_range("vector index out of range");
				return _start[pos];
			}

			const_reference		at( size_type pos ) const {
				if (pos > _size)
					throw std::out_of_range("vector index out of range");
				return _start[pos];
			}

			reference			operator [] ( size_type pos ) { return _start[pos]; }
			const_reference		operator [] ( size_type pos ) const { return _start[pos]; }

			reference			front( void ) { return *begin(); }
			const_reference		front( void ) const { return *begin(); }

			reference			back( void ) { return *(end() - 1); }
			const_reference		back( void ) const { return *(end() - 1); }

			value_type			*data( void ) { return _start; }
			const value_type	*data( void ) const { return _start; }



			//MARK: - Iterators ✓

			iterator				begin( void ) { return iterator( _start ); }
			const_iterator			begin( void ) const { return const_iterator( _start ); }

			iterator				end( void ) { return iterator( _start + _size ); }
			const_iterator			end( void ) const { return const_iterator( _start + _size ); }

			reverse_iterator		rbegin( void ) { return reverse_iterator( _start + _size ); }
			const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator( _start + _size ); }

			reverse_iterator		rend( void ) { return reverse_iterator( _start ); }
			const_reverse_iterator	rend( void ) const { return const_reverse_iterator( _start ); }



			//MARK: - Capacity ✓

			bool		empty( void ) const { return _size == 0; }
			size_type	size( void ) const { return _size; }
			size_type	max_size( void ) const { return _alloc.max_size(); }
			size_type	capacity( void ) const { return _capacity; }
			
			void		reserve( size_type new_cap ) {
				if (new_cap < _capacity)
					return;
				pointer	new_start = _alloc.allocate( new_cap );
				for(size_type i = 0; i < _size; ++i) {
					_alloc.construct( new_start + i, _start[i] );
					_alloc.destroy( _start + i );
				}
				_alloc.deallocate( _start, _capacity );
				_start = new_start;
				_capacity = new_cap;
			}
			


			//MARK: - Modifiers

			void		clear( void ) {
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy( it.operator->() );
				_size = 0;
			}

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




	//MARK: - Class Constructors

	template < class T, class Alloc >
	ft::vector<T, Alloc>::vector( const allocator_type &alloc )
	:
		_alloc( alloc ),
		_start( NULL ),
		_size( 0 ),
		_capacity( 0 )
	{}

	template < class T, class Alloc >
	ft::vector<T, Alloc>::vector( size_type count,
							 const value_type &value,
							 const allocator_type &alloc )
	:
		_alloc( alloc ),
		_size( count )
	{
		_capacity = count;
		_start = _alloc.allocate( _capacity );

		for (iterator it = begin(); it != end(); ++it)
			_alloc.construct( &(*it), value );
	}

	template < class T, class Alloc >
	template < class InputIterator >
	ft::vector<T, Alloc>::vector( InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * )
	:
		_alloc( alloc ),
		_size( 0 )
	{
		for (InputIterator it; it != last; ++it)
			++_size;
		_capacity = _size;
		_start = _alloc.allocate( _capacity );
		for (iterator it = begin(); first !=  last; ++first, ++it)
			*it = *first;
	}




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
