#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

# include <iostream>
# include "utils.hpp"
# include <vector>

namespace ft {

	template < typename T >
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

		private:
			pointer	num;

		public:

			//MARK: - Class Constructor

			random_access_iterator( void ) : num( 0 ) {}
			
			random_access_iterator( pointer num ) : num( num ) {}


			//MARK: - Class Copy Constructor

			random_access_iterator( const random_access_iterator &src ) : ( src.num ) {}


			//MARK: - Class Assignation Overload

			random_access_iterator	&operator = ( const random_access_iterator &src ) {
				if (this != &src)
					num = src.num;
				return *this;
			}


			//MARK: - Class Distructor

			~random_access_iterator( void ) {}


			//MARK: - Class Methods

			pointer	getPointer( void ) {
				return num;
			}


			//MARK: - Class Overloads

			reference	operator * ( void ) const {
				return *num;
			}

			pointer		operator -> ( void ) {
				return &(this->operator*());
			}

			random_access_iterator	&operator ++ ( void ) {
				++num;
				return *this;
			}

			random_access_iterator	operator ++ ( int ) {
				random_access_iterator	tmp( *this );

				++num;
				return tmp;
			}

			random_access_iterator	&operator -- ( void ) {
				--num;
				return *this;
			}

			random_access_iterator	operator -- ( int ) {
				random_access_iterator	tmp( *this );

				--num;
				return tmp;
			}

			random_access_iterator	operator + ( difference_type n ) const {
				return num + n;
			}

			random_access_iterator	operator - ( difference_type n ) const {
				return num - n;
			}

			random_access_iterator	&operator += ( difference_type n ) {
				num += n;
				return *this;
			}

			random_access_iterator	&operator -= ( difference_type n ) {
				num -= n;
				return *this;
			}

			reference	operator [] ( difference_type n ) const {
				return num[n];
			}

			operator	random_access_iterator<const T> ( void ) const {
				return random_access_iterator<const T>( num );
			}
		
	};

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
		return lhs.getPointer() + rhs.getPointer();
	}


}


#endif
