#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include "vector.hpp"

namespace ft {

	template < class T, class Container = ft::vector<T> >
	class stack {

		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		private:
			Container	c;

		public:

			// MARK: - Class Constructor

			explicit stack( const Container &cont = Container() ) : c( cont )	{}


			// MARK: - Class Copy Constructor

			stack( const stack &src ) : c( src.c ) {}


			// MARK: - Class Distructor

			~stack( void ) {}


			// MARK: - Class Assignation Overload

			stack	&operator = ( const stack &src ) {
				if ( this != &src )
					c = src.c;
				return *this;
			}

			
			// MARK: - Element Access

			reference	top(  void )			{ return c.back(); }
			const_reference	top( void ) const	{ return c.back(); }


			// MARK: - Capacity

			bool	empty( void ) const			{ return c.empty(); }
			size_type	size( void ) const		{ return c.size(); }


			// MARK: - Modifiers

			void	push( const value_type &value ) { c.push_back( value ); }
			void	pop( void )						{ c.pop_back(); }


			// MARK: - Friend Functions

			friend bool	operator == ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs )	{ return lhs.c == rhs.c; }
			friend bool	operator != ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs )	{ return lhs.c != rhs.c; }
			friend bool	operator < ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs )	{ return lhs.c < rhs.c; }
			friend bool	operator <= ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs )	{ return lhs.c <= rhs.c; }
			friend bool	operator > ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs )	{ return lhs.c > rhs.c; }
			friend bool	operator >= ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs )	{ return lhs.c >= rhs.c; }

	};


	// MARK: - Non Member Functions

	template < class T, class Container >
	bool	operator == ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs ) {
		return lhs.c == rhs.c;
	}

	template < class T, class Container >
	bool	operator != ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs ) {
		return lhs.c != rhs.c;
	}

	template < class T, class Container >
	bool	operator < ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs ) {
		return lhs.c < rhs.c;
	}

	template < class T, class Container >
	bool	operator <= ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs ) {
		return lhs.c <= rhs.c;
	}

	template < class T, class Container >
	bool	operator > ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs ) {
		return lhs.c > rhs.c;
	}

	template < class T, class Container >
	bool	operator >= ( const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs ) {
		return lhs.c >= rhs.c;
	}


}

#endif
