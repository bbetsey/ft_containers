# include "vector.hpp"


//MARK: - Class Constructor

template < class T, class Alloc >
ft::vector<T, Alloc>::vector( const allocator_type &alloc = allocator_type() )
:
	_alloc( alloc ),
	_start( NULL ),
	_size( 0 ),
	_capacity( 0 )
{}

template < class T, class Alloc >
ft::vector<T, Alloc>::vector( size_type count,
								const value_type &value = value_type(),
								const allocator_type &alloc = allocator_type() )
:
	_alloc( alloc ),
	_start( NULL ),
	_size( 0 ),
	_capacity( 0 )
{
	_start = _alloc.allocate( count );
	_size = count;
	_capacity = count;
	for (int i = 0; i < count; ++i)
		_alloc.construct( _start + i, value );
}


//MARK: - Class Copy Constructor

template < class T, class Alloc >
ft::vector<T, Alloc >::vector( const vector &src )
:
	_alloc( src.alloc ),
	_start( NULL ),
	_size( src._size ),
	_capacity( src._capacity )
{
	insert( begin(), src.begin(), src.end() );
}

template < class T, class Alloc >
typename ft::vector<T, Alloc>::vector
&ft::vector<T, Alloc>::operator = ( const vector &src )
:
	_alloc( src.alloc ),
	_start( NULL ),
	_size( src._size ),
	_capacity( src._capacity )
{
	if (this != &src) {
		clear();
		insert( begin(), src.begin(), src.end() );
	}
	return *this;
}
