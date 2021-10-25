# include "reverse_iterator.hpp"


//MARK: - Class Constructor

template < class Iterator >
ft::reverse_iterator<Iterator>::reverse_iterator( void ) : it() {}

template < class Iterator >
ft::reverse_iterator<Iterator>::reverse_iterator( typename ft::reverse_iterator<Iterator>::iterator_type it ) : it( it ) {}


//MARK: - Class Copy Constructor

template < class Iterator>
template < class U >
ft::reverse_iterator<Iterator>::reverse_iterator( const ft::reverse_iterator<U> &src ) : it( src.it ) {}


//MARK: - Class Assignation Overload

template < class Iterator >
template < class U >
ft::reverse_iterator<Iterator>
&ft::reverse_iterator<Iterator>::operator = ( const ft::reverse_iterator<U> &src ) {
	if (this != &src)
		it = src.it;
	return *this;
}


//MARK: - Class Distructor

template < class Iterator >
ft::reverse_iterator<Iterator>::~reverse_iterator( void ) {}


//MARK: - Class Methods

template < class Iterator >
typename ft::reverse_iterator<Iterator>::iterator_type
ft::reverse_iterator<Iterator>::base( void ) const {
	return it;
}


//MARK: - Class Valid Expressions Overload

template < class Iterator >
typename ft::reverse_iterator<Iterator>::reference
ft::reverse_iterator<Iterator>::operator * ( void ) const {
	Iterator	tmp( it );
	return *(--tmp);
}

template < class Iterator >
typename ft::reverse_iterator<Iterator>::pointer
ft::reverse_iterator<Iterator>::operator -> ( void ) const {
	return std::addressof( operator*() );
}

template < class Iterator >
typename ft::reverse_iterator<Iterator>::reference
ft::reverse_iterator<Iterator>::operator [] ( typename ft::reverse_iterator<Iterator>::difference_type n ) const {
	return base()[- n - 1];
}

template < class Iterator >
ft::reverse_iterator<Iterator>
&ft::reverse_iterator<Iterator>::operator ++ ( void ) {
	--it;
	return *this;
}

template < class Iterator >
ft::reverse_iterator<Iterator>
ft::reverse_iterator<Iterator>::operator ++ ( int ) {
	ft::reverse_iterator	tmp( *this );
	--it;
	return tmp;
}

template < class Iterator >
ft::reverse_iterator<Iterator>
&ft::reverse_iterator<Iterator>::operator -- ( void ) {
	++it;
	return *this;
}

template < class Iterator >
ft::reverse_iterator<Iterator>
ft::reverse_iterator<Iterator>::operator -- ( int ) {
	ft::reverse_iterator	tmp( *this );
	++it;
	return tmp;
}

template < class Iterator >
ft::reverse_iterator<Iterator>
ft::reverse_iterator<Iterator>::operator + ( typename ft::reverse_iterator<Iterator>::difference_type n ) const {
	return ft::reverse_iterator( base() - n );
}

template < class Iterator >
ft::reverse_iterator<Iterator>
ft::reverse_iterator<Iterator>::operator - ( typename ft::reverse_iterator<Iterator>::difference_type n ) const {
	return ft::reverse_iterator( base() + n );
}

template < class Iterator >
ft::reverse_iterator<Iterator>
&ft::reverse_iterator<Iterator>::operator += ( typename ft::reverse_iterator<Iterator>::difference_type n ) {
	it -= n;
	return *this;
}

template < class Iterator >
ft::reverse_iterator<Iterator>
&ft::reverse_iterator<Iterator>::operator -= ( typename ft::reverse_iterator<Iterator>::difference_type n ) {
	it += n;
	return *this;
}
