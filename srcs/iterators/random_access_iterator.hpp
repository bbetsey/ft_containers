#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"

namespace ft {


	template < typename T >
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {


		private:
		
			pointer		ptr;


		public:

			//MARK: - Member types

			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category		iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference				reference;


			//MARK: - Class Constructors

			random_access_iterator( void );
			random_access_iterator( pointer ptr );


			//MARK: - Class Copy Constructor

			random_access_iterator( const random_access_iterator &src );


			//MARK: - Class Assignation Overload

			random_access_iterator	&operator = ( const random_access_iterator &src );


			//MARK: - Class Distructor

			~random_access_iterator( void );


			//MARK: - Class Methods ( getters )

			pointer	getPointer( void );


			//MARK: - Class Valid Expressions Overload

			reference	operator * ( void ) const;
			pointer		operator -> ( void ) const;

			random_access_iterator	&operator ++ ( void );
			random_access_iterator	operator ++ ( int );
			random_access_iterator	&operator ++ ( void );
			random_access_iterator	operator ++ ( int );

			random_access_iterator	operator + ( difference_type n ) const;
			random_access_iterator	operator - ( difference_type n ) const;

			random_access_iterator	&operator += ( difference_type n );
			random_access_iterator	&operator -= ( difference_type n );

			reference	operator [] ( difference_type n ) const;

			operator	random_access_iterator<const T> ( void ) const;

	};



}


#endif
