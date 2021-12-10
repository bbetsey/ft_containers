#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "../iterators/node_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utils/pair.hpp"
# include "../utils/node.hpp"
# include "../utils/tree.hpp"

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map {

		public:

			// MARK: - Member Types

			typedef Key																			key_type;
			typedef T																			mapped_type;
			typedef typename ft::pair<const Key, T>												value_type;
			typedef std::size_t																	size_type;
			typedef std::ptrdiff_t																difference_type;
			typedef Compare																		key_compare;
			typedef Allocator																	allocator_type;
			typedef value_type&																	reference;
			typedef const value_type&															const_reference;
			typedef typename Allocator::pointer													pointer;
			typedef typename Allocator::const_pointer											const_pointer;
			typedef ft::node_iterator<ft::node<value_type>*, value_type>						iterator;
			typedef ft::node_iterator<const ft::node<value_type>*, value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>												reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>										const_reverse_iterator;
			typedef typename allocator_type::template rebind<ft::node<value_type> >::other		allocator_rebind_node;
			typedef typename allocator_type::template rebind<ft::rbTree<value_type> >::other	allocator_rebind_tree;
			

			// MARK: - Member Class

			class value_compare : public std::binary_function<value_type, value_type, bool> {

				friend class ft::map;

				protected:

					Compare	comp;
					value_compare( Compare c ) : comp( c ) {}

				public:

					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					result_type	operator () ( const value_type &x, const value_type &y ) const {
						return comp( x.first, y.first );
					}

			};

		
		private:

			allocator_type			_pair_alloc;
			allocator_rebind_node	_node_alloc;
			allocator_rebind_tree	_tree_alloc;
			key_compare				_comp;
			rbTree<value_type>*		_tree = nullptr;

		
		public:

			
			// MARK: - Class Constructors

			map( void )	{ treeInit(); }

			explicit map( const Compare &comp, const Allocator &alloc = Allocator() ) : _comp( comp ), _pair_alloc( alloc ) {
				treeInit();
			}

			template < class InputIt >
			map( InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator() )
			:
				_pair_alloc( alloc ),
				_comp( comp )
			{
				treeInit();
				for ( ; first != last; ++first )
					insert( ft::make_pair( first->first, first->second ) );
			}


			// MARK: - Class Copy Constructor

			map( const map &src ) { *this = src; }


			// MARK: - Class Assignation Overload

			map	&operator = ( const map &src ) {
				if ( this != &src ) {
					_comp = src._comp;
					_pair_alloc = src._pair_alloc;
					if ( _tree )
						burnTheTree();
					_size = src._size;
					_tree = _tree_alloc.allocate( sizeof(rbTree<value_type>) );
					_tree_alloc.construct( _tree, *src._tree );
					copyTree( src._tree->_root );
					return *this;
				}
			}


			// MARK: - Class Distructor

			~map( void ) {
				burnTheTree();
			}


			// MARK: - Class Getters

			allocator_type	get_allocator( void ) const { return _pair_alloc; }


			// MARK: - Element Access

			mapped_type			&at( const key_type &key ) {
				iterator result = find( key );
				if ( result == end() )
					throw std::out_of_range( "key not found" );
				return result->second;
			}
			const mapped_type	&at( const key_type &key ) const {
				iterator result = find( key );
				if ( result == end() )
					throw std::out_of_range( "key not found" );
				return result->second;
			}

			mapped_type			&operator [] ( const key_type &key )	{ return insert( ft::make_pair( key, mapped_type() ) ).first->second; }


			// MARK: - Iterators

			iterator		begin( void )		{ return _tree->begin(); }
			const_iterator	begin( void ) const	{ return _tree->begin(); }

			iterator		end( void )			{ return _tree->end(); }
			const_iterator	end( void ) const	{ return _tree->end(); }

			reverse_iterator		rbegin( void )			{ return reverse_iterator( iterator( _tree->last() ) ); } // or _tree->last()
			const_reverse_iterator	rbegin( void ) const	{ return const_reverse_iterator( iterator( _tree->last() ) ); }

			reverse_iterator		rend( void )			{ return reverse_iterator( iterator( _tree->end() ) ); }
			const_reverse_iterator	rend( void ) const		{ return const_reverse_iterator( iterator( _tree->end() ) ); }


			// MARK: - Capacity

			bool		empty( void ) const	{ return _size == 0; }
			size_type	size( void ) const	{ return _size; }
			size_type	max_size( void ) const { return (size_type)std::numeric_limits<difference_type>::max(); }


			// MARK: - Modifiers

			void	clear( void ) {
				burnTheTree();
				_tree = _tree_alloc.allocate( sizeof(rbTree<value_type) );
				_tree_alloc.construct( _tree );
			}


			ft::pair<iterator, bool>	insert( const value_type &value ) {
				ft::pair<iterator, bool> place = findPlace( _tree->_root, value );
				if ( !place.second ) return place;
			}



		private:

			void	treeInit( void ) {
				_tree = _tree_alloc.allocate( sizeof(_tree<value_type>) );
				_tree_alloc.construct( _tree );
				_tree->_root = _node_alloc.allocate( sizeof(node<value_type>) );
				_node_alloc.construct( _tree->_root );
			}

			ft::pair<iterator, bool>	findPlace( node<value_type> *root, const value_type &value ) {
				while ( !root->isLeaf ){
					if ( root->value.first == value.first ) return ft::make_pair( root, false );
					root = ( _comp( value.first, root->value.first ) )
						? root->left
						: root->right;
				}
				return ft::make_pair( root, true );
			}

			node<value_type>	*leafInit( iterator place ) {
				node<value_type>	*leaf;

				leaf = _node_alloc.allocate( sizeof(node<value_type>) );
				_node_alloc.construct( leaf->value, value_type() )
			}

			void	fillNode( iterator place, const value_type &value ) {
				place->value = value;
				place->right = _node_alloc.allocate( sizeof(node<value_type) );
			}
			

	};

}

#endif
