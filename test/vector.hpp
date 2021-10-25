#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

template < typename T, typename Alloc = std::allocator<T> >
class vector {
	private:
		Alloc	alloc;
		T		*start;
		size_t	size;
		size_t	capacity;

	public:
		explicit vector( const Alloc &alloc );
		explicit vector( size_t count, const T &value = T(), const Alloc &alloc = Alloc() );

		vector	&operator = ( const vector &src );

		//getters
		size_t	capacity( void ) const;
		size_t	max_size( void ) const;
		size_t	size( void ) const;
		bool	empty( void ) const;

		void	reserve( size_t new_cap );
		void	clear( void );
		
};

#endif
