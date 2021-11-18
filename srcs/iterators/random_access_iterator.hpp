#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"

namespace ft {


	template < typename T >
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {

		public:

			//MARK: - Member types

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;
		

		private:

			pointer		ptr;


		public:


			//MARK: - Class Constructors

			random_access_iterator( void )  : ptr( NULL )	{}
			random_access_iterator( pointer ptr ) : ptr( ptr )	{}


			//MARK: - Class Copy Constructor

			random_access_iterator( const random_access_iterator &src )	{ *this = src; }


			//MARK: - Class Assignation Overload

			random_access_iterator	&operator = ( const random_access_iterator &src ) {
				if (this != &src)
					ptr = src.ptr;
				return *this;
			}


			//MARK: - Class Distructor

			~random_access_iterator( void ) {}


			//MARK: - Class Methods ( getters )

			pointer	getPointer( void )							{ return ptr; }
			pointer	getPointer( void ) const					{ return ptr; }


			//MARK: - Class Valid Expressions Overload

			reference	operator * ( void ) const				{ return *ptr; }
			pointer		operator -> ( void ) const				{ return &(*ptr); }

			random_access_iterator	&operator ++ ( void )		{ ++ptr; return *this; }

			random_access_iterator	operator ++ ( int ) {
				random_access_iterator	tmp( *this );
				++tmp;
				return tmp;
			}

			random_access_iterator	&operator -- ( void )		{ --ptr; return *this; }
			
			random_access_iterator	operator -- ( int ) {
				random_access_iterator	tmp( *this );
				--tmp;
				return tmp;
			}

			random_access_iterator	operator + ( difference_type n ) const	{ return ptr + n; }
			random_access_iterator	operator - ( difference_type n ) const	{ return ptr - n; }

			random_access_iterator	&operator += ( difference_type n )		{ ptr += n; return *this; }
			random_access_iterator	&operator -= ( difference_type n )		{ ptr -= n; return *this; }

			reference	operator [] ( difference_type n ) const				{ return ptr[n]; }

			operator	random_access_iterator<const T> ( void ) const		{ return random_access_iterator<const T>( ptr ); }

	};


	//MARK: - Not Member Functions

	template < typename T >
	bool	operator == ( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {
		return lhs.getPointer() == rhs.getPointer();
	}

	template < typename TL, typename TR >
	bool	operator == ( const ft::random_access_iterator<TL> lhs, const ft::random_access_iterator<TR> rhs ) {
		return lhs.getPointer() == rhs.getPointer();
	}

	template < typename T >
	bool	operator != ( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {
		return lhs.getPointer() != rhs.getPointer();
	}

	template < typename TL, typename TR >
	bool	operator != ( const ft::random_access_iterator<TL> lhs, const ft::random_access_iterator<TR> rhs ) {
		return lhs.getPointer() != rhs.getPointer();
	}

	template < typename T >
	bool	operator < ( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {
		return lhs.getPointer() < rhs.getPointer();
	}

	template < typename TL, typename TR >
	bool	operator < ( const ft::random_access_iterator<TL> lhs, const ft::random_access_iterator<TR> rhs ) {
		return lhs.getPointer() < rhs.getPointer();
	}

	template < typename T >
	bool	operator > ( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {
		return lhs.getPointer() > rhs.getPointer();
	}

	template < typename TL, typename TR >
	bool	operator > ( const ft::random_access_iterator<TL> lhs, const ft::random_access_iterator<TR> rhs ) {
		return lhs.getPointer() > rhs.getPointer();
	}

	template < typename T >
	bool	operator <= ( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {
		return lhs.getPointer() <= rhs.getPointer();
	}

	template < typename TL, typename TR >
	bool	operator <= ( const ft::random_access_iterator<TL> lhs, const ft::random_access_iterator<TR> rhs ) {
		return lhs.getPointer() <= rhs.getPointer();
	}

	template < typename T >
	bool	operator >= ( const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs ) {
		return lhs.getPointer() >= rhs.getPointer();
	}

	template < typename TL, typename TR >
	bool	operator >= ( const ft::random_access_iterator<TL> lhs, const ft::random_access_iterator<TR> rhs ) {
		return lhs.getPointer() >= rhs.getPointer();
	}

	template < typename T >
	typename ft::random_access_iterator<T>
	operator + ( typename ft::random_access_iterator<T>::difference_type n,
				 typename ft::random_access_iterator<T> &src ) {
		return src.operator+( n );
	}

	template < typename T >
	typename ft::random_access_iterator<T>::difference_type
	operator - ( typename ft::random_access_iterator<T> lhs,
				 typename ft::random_access_iterator<T> rhs ) {
		return lhs.getPointer() - rhs.getPointer();
	}

	template < typename TL, typename TR >
	typename ft::random_access_iterator<TL>::difference_type
	operator - ( typename ft::random_access_iterator<TL> lhs,
				 typename ft::random_access_iterator<TR> rhs ) {
		return lhs.getPointer() - rhs.getPointer();
	}

}


#endif
