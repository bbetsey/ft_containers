# include "random_access_iterator.hpp"


//MARK: - Class Constructor

template < class T >
ft::random_access_iterator<T>::random_access_iterator( void ) : ptr( 0 ) {}

template < class T >
ft::random_access_iterator<T>::random_access_iterator( pointer ptr ) : ptr( ptr ) {}


//MARK: - Class Copy Constructor

template < class T >
ft::random_access_iterator<T>::random_access_iterator( const random_access_iterator &src ) {
	*this = src;
}


//MARK: - Class Assignation Overload

template < class T >
ft::random_access_iterator<T>	&ft::random_access_iterator<T>::operator = ( const random_access_iterator &src ) {
	if (this != &src)
		ptr = src.ptr;
	return *this;
}


//MARK: - Class Distructor

template < class T >
ft::random_access_iterator<T>::~random_access_iterator( void ) {}


//MARK: - Class Methods ( getter )

template < class T >
typename ft::random_access_iterator<T>::pointer
ft::random_access_iterator<T>::getPointer( void ) {
	return ptr;
}


//MARK: - Class Valid Expressions Overload

template < class T >
typename ft::random_access_iterator<T>::reference
ft::random_access_iterator<T>::operator * ( void ) const {
	return *ptr;
}

template < class T >
typename ft::random_access_iterator<T>::pointer
ft::random_access_iterator<T>::operator -> ( void ) const {
	return &(*ptr);
}

template < class T >
ft::random_access_iterator<T>
&ft::random_access_iterator<T>::operator ++ ( void ) {
	++ptr;
}

template < class T >
ft::random_access_iterator<T>
ft::random_access_iterator<T>::operator ++ ( int ) {
	random_access_iterator	tmp( *this );
	++tmp;
	return tmp;
}

template < class T >
ft::random_access_iterator<T>
&ft::random_access_iterator<T>::operator -- ( void ) {
	--ptr;
}

template < class T >
ft::random_access_iterator<T>
ft::random_access_iterator<T>::operator -- ( int ) {
	random_access_iterator	tmp( *this );
	--ptr;
	return tmp;
}

template < class T >
ft::random_access_iterator<T>
ft::random_access_iterator<T>::operator + ( typename ft::random_access_iterator<T>::difference_type n ) const {
	ptr + n;
}

template < class T >
ft::random_access_iterator<T>
ft::random_access_iterator<T>::operator - ( typename ft::random_access_iterator<T>::difference_type n ) const {
	ptr - n;
}

template < class T >
ft::random_access_iterator<T>
&ft::random_access_iterator<T>::operator += ( typename ft::random_access_iterator<T>::difference_type n ) {
	ptr += n;
	return *this;
}

template < class T >
ft::random_access_iterator<T>
&ft::random_access_iterator<T>::operator -= ( typename ft::random_access_iterator<T>::difference_type n ) {
	ptr -= n;
	return *this;
}

template < class T >
typename ft::random_access_iterator<T>::reference
ft::random_access_iterator<T>::operator [] ( typename ft::random_access_iterator<T>::difference_type n ) const {
	return ptr[n];
}

template < class T >
ft::random_access_iterator<T>::operator
ft::random_access_iterator<const T>( void ) const {
	return random_access_iterator<const T>( ptr );
}
