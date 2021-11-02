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


			// MARK: - Class Constructors ✓

			explicit vector( const allocator_type &alloc = allocator_type() );

			explicit vector( size_type count,
							 const value_type &value = value_type(),
							 const allocator_type &alloc = allocator_type() );

			template < class InputIterator >
			vector( InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0 );


			// MARK: - Class Copy Constructor ✓

			vector( const vector &src );


			// MARK: - Class Assignation Overload ✓

			vector	&operator = ( const vector &src );


			// MARK: - Class Distructor ✓

			~vector( void );


			// MARK: - Class Methods ( getters ) ✓

			allocator_type	get_allocator( void ) const;


			// MARK: - Class Methods ✓

			void	assign( size_type count, const value_type &value );

			template < class InputIterator >
			void	assign( InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0 );


			// MARK: - Class Element Access

			reference			at( size_type pos );
			const_reference		at( size_type pos ) const;

			reference			operator [] ( size_type pos );
			const_reference		operator [] ( size_type pos ) const;

			reference			front( void );
			const_reference		front( void ) const;

			reference			back( void );
			const_reference		back( void ) const;


			// MARK: - Iterators ✓

			iterator				begin( void );
			const_iterator			begin( void ) const;

			iterator				end( void );
			const_iterator			end( void ) const;

			reverse_iterator		rbegin( void );
			const_reverse_iterator	rbegin( void ) const;

			reverse_iterator		rend( void );
			const_reverse_iterator	rend( void ) const;


			// MARK: - Capacity ✓

			bool		empty( void ) const;
			size_type	size( void ) const;
			size_type	max_size( void ) const;
			size_type	capacity( void ) const;		
			void		reserve( size_type new_cap );
			

			// MARK: - Modifiers

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



	
	// MARK: - Class Constructors

	// » default constructor

	template < class T, class Alloc >
	ft::vector<T, Alloc>::vector( const allocator_type &alloc )
	:
		_alloc( alloc ),
		_start( NULL ),
		_size( 0 ),
		_capacity( 0 )
	{}

	// » count constructor

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
			_alloc.construct( it.operator->(), value );
	}

	// » range constructor

	template < class T, class Alloc >
	template < class InputIterator >
	ft::vector<T, Alloc>::vector( InputIterator first, InputIterator last,
					const allocator_type &alloc,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * )
	:
		_alloc( alloc ),
		_size( 0 )
	{
		for (InputIterator it; it != last; ++it)
			++_size;
		_capacity = _size;
		_start = _alloc.allocate( _capacity );
		for (iterator it = begin(); first != last; ++first, ++it)
			_alloc.construct( it.operator->(), *first );
	}



	// MARK: - Class Copy Constructor

	template < class T, class Alloc >
	ft::vector<T, Alloc>::vector( const vector &src )
	:
		_alloc( src._alloc ),
		_size( 0 ),
		_capacity( 0 ),
		_start( NULL )
	{
		insert( begin(), src.begin(), src.end() );
	}



	// MARK: - Class Assignation Overload

	template < class T, class Alloc >
	ft::vector<T, Alloc>
	&ft::vector<T, Alloc>::operator = ( const vector &src ) {
		if (this != &src) {
			clear();
			insert( begin(), src.begin(), src.end() );
		}
		return *this;
	}



	// MARK: - Class Distructor

	template < class T, class Alloc >
	ft::vector<T, Alloc>::~vector( void ) {
		for (iterator it = begin(); it != end(); ++it)
			_alloc.destroy( &(*it) );
		_alloc.deallocate( _start, _capacity );
	}



	// MARK: - Class Methods ( getters )

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::allocator_type
	ft::vector<T, Alloc>::get_allocator( void ) const {
		return _alloc;
	}



	// MARK: - Class Methods

	template < class T, class Alloc >
	void	ft::vector<T, Alloc>::assign( size_type count, const value_type &value ) {
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

	template < class T, class Alloc >
	template < class InputIterator >
	void	ft::vector<T, Alloc>::assign( InputIterator first, InputIterator last,
										  typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * ) {
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



	// MARK: - Class Element Access

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::reference
	ft::vector<T, Alloc>::at( size_type pos ) {
		if (pos > _size)
			throw std::out_of_range("vector index out of range");
		return _start[pos];
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::const_reference
	ft::vector<T, Alloc>::at( size_type pos ) const {
		if (pos > _size)
			throw std::out_of_range("vector index out of range");
		return _start[pos];
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::reference
	ft::vector<T, Alloc>::operator [] ( size_type pos ) {
		return _start[pos];
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc >::const_reference
	ft::vector<T, Alloc>::operator [] ( size_type pos ) const {
		return _start[pos];
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::reference
	ft::vector<T, Alloc>::front( void ) {
		return *begin();
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::const_reference
	ft::vector<T, Alloc>::front( void ) const {
		return *begin();
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::reference
	ft::vector<T, Alloc>::back( void ) {
		return *(end() - 1);
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::const_reference
	ft::vector<T, Alloc>::back( void ) const {
		return *(end() - 1);
	}



	// MARK: - Iterators

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::iterator
	ft::vector<T, Alloc>::begin( void ) {
		return iterator( _start );
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::const_iterator
	ft::vector<T, Alloc>::begin( void ) const {
		return iterator( _start );
	}
	
	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::iterator
	ft::vector<T, Alloc>::end( void ) {
		return iterator( _start + _size );
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::const_iterator
	ft::vector<T, Alloc>::end( void ) const {
		return iterator( _start + _size );
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::reverse_iterator
	ft::vector<T, Alloc>::rbegin( void ) {
		return reverse_iterator( _start + _size );
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::const_reverse_iterator
	ft::vector<T, Alloc>::rbegin( void ) const {
		return reverse_iterator( _start + _size );
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::reverse_iterator
	ft::vector<T, Alloc>::rend( void ) {
		return reverse_iterator( _start );
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::const_reverse_iterator
	ft::vector<T, Alloc>::rend( void ) const {
		return reverse_iterator( _start );
	}



	// MARK: - Capacity

	template < class T, class Alloc >
	bool	ft::vector<T, Alloc>::empty( void ) const {
		return _size == 0;
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::size_type
	ft::vector<T, Alloc>::size( void ) const {
		return _size;
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::size_type
	ft::vector<T, Alloc>::max_size( void ) const {
		return _alloc.max_size();
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::size_type
	ft::vector<T, Alloc>::capacity( void ) const {
		return _capacity;
	}

	template < class T, class Alloc >
	void	ft::vector<T, Alloc>::reserve( size_type new_cap ) {
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



	// MARK: - Modifiers

	template < class T, class Alloc >
	void	ft::vector<T, Alloc>::clear( void ) {
		for (iterator it = begin(); it != end(); ++it)
			_alloc.destroy( it.operator->() );
		_size = 0;
	}

	template < class T, class Alloc >
	typename ft::vector<T, Alloc>::iterator
	ft::vector<T, Alloc>::insert( iterator pos, const value_type &value ) {
		pointer		tmp;
		size_type	capacity_tmp = _capacity;
		size_type 	i = 0;
		size_type	ret = 0;

		if ( _capacity == _size )
			++_capacity;
		tmp = _alloc.allocate( _capacity );
		for ( iterator it = begin(); it != end(); ++it, ++i ) {
			if ( it == pos ) {
				_alloc.construct( tmp + i, value );
				std::cout << *(tmp + i) << std::endl;
				ret = i;
				++_size;
				++i;
			}
			_alloc.construct( tmp + i, *it );
			std::cout << *(tmp + i) << std::endl;
		}
		if ( pos == end() ) {
			_alloc.construct( tmp + i, value );
			ret = i;
			++_size;
		}
		// for ( iterator it = begin(); it != end(); ++it )
		// 	_alloc.destroy( it->operator->() );
		_alloc.deallocate( _start, capacity_tmp );
		_start = tmp;
		return _start + ret;
	}

	template < class T, class Alloc >
	void	ft::vector<T, Alloc>::insert( iterator pos, size_type count, const value_type &value ) {
		pointer		tmp;
		size_type	capacity_tmp = _capacity;
		size_type 	i = 0;

		if ( _size + count >= _capacity )
			_capacity += count;
		tmp = _alloc.allocate( _capacity );
		for ( iterator it = begin(); it != end(); ++it, ++i ) {
			if ( it == pos ) {
				while ( count-- ) {
					_alloc.construct( tmp + i, value );
					++_size;
					++i;
				}
			}
			_alloc.construct( tmp + i, *it );
		}
		if ( pos == end() ) {
			while ( count-- ) {
				_alloc.construct( tmp + i, value );
				++_size;
				++i;
			}
		}
		for ( iterator it = begin(); it != end(); ++it )
			_alloc.destroy( it->operator->() );
		_alloc.deallocate( _start, capacity_tmp );
		_start = tmp;
	}



	// ---------------------------------------------------------------------------------------------------------------------------------

	// MARK: - Not Member Functions

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
