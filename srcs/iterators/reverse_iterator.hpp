#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include "iterator_traits.hpp"


namespace ft {

	template < class Iterator >
	class reverse_iterator {
		
		public:

			//MARK: - Member Types

			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

		
		private:
			iterator_type	it;


		public:

			//MARK: - Class Constructor
			
			reverse_iterator( void ) : it()	{}
			
			explicit reverse_iterator( iterator_type it ) : it( it ) {}


			//MARK: - Class Copy Constructor

			template < class U >
			reverse_iterator( const reverse_iterator<U> &src ) : it( src.it ) {}

			
			//MARK: - Class Assignation Overload

			template < class U >
			reverse_iterator	&operator = ( const reverse_iterator<U> &src ) {
				if (this != &src)
					it = src.it;
				return *this;
			}


			//MARK: - Class Distructor

			~reverse_iterator( void ) {}


			//MARK: - Class Methods

			iterator_type	base( void ) const 	{ return it; }


			//MARK: - Class Valid Expressions Overload

			reference	operator * ( void ) 					{ return *it; }
			pointer		operator -> ( void )					{ return std::addressof( operator*() ); }
			reference	operator [] ( difference_type n ) const	{ return it[- n - 1]; }

			reverse_iterator	&operator ++ ( void )			{ --it; return *this; }
			reverse_iterator	&operator -- ( void )			{ ++it; return *this; }
			
			reverse_iterator	operator ++ ( int ) {
				reverse_iterator	tmp( *this );
				--it;
				return tmp;
			}
			
			reverse_iterator	operator -- ( int ) {
				reverse_iterator	tmp( *this );
				++it;
				return tmp;
			}


			reverse_iterator	operator + ( difference_type n ) const	{ return reverse_iterator( it - n ); }
			reverse_iterator	operator - ( difference_type n ) const	{ return reverse_iterator( it + n ); }

			reverse_iterator	&operator += ( difference_type n ) 		{ it -= n; return *this; }
			reverse_iterator	&operator -= ( difference_type n )		{ it += n; return *this; }

	};


	//MARK: - Not Member Functions

	template < class Iterator1, class Iterator2 >
	bool	operator == ( const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs ) {
		return lhs.base() == rhs.base();
	}

	template < class Iterator1, class Iterator2 >
	bool	operator != ( const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs ) {
		return lhs.base() != rhs.base();
	}

	template < class Iterator1, class Iterator2 >
	bool	operator < ( const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs ) {
		return lhs.base() < rhs.base();
	}

	template < class Iterator1, class Iterator2 >
	bool	operator <= ( const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs ) {
		return lhs.base() <= rhs.base();
	}

	template < class Iterator1, class Iterator2 >
	bool	operator > ( const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs ) {
		return lhs.base() > rhs.base();
	}

	template < class Iterator1, class Iterator2 >
	bool	operator >= ( const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs ) {
		return lhs.base() >= rhs.base();
	}

	template < class Iterator >
	reverse_iterator<Iterator>
	operator + ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it ) {
		return it.base() - n;
	}

	template < class Iterator >
	typename reverse_iterator<Iterator>::difference_type
	operator - ( const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs ) {
		return lhs.base() - rhs.base();
	}

}

#endif
