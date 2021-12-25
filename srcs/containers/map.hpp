#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "../iterators/node_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utils/pair.hpp"
# include "../utils/node.hpp"
# include "../utils/tree.hpp"
# include "../utils/equal.hpp"
# include "../utils/lexicographical_compare.hpp"

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map {

		public:

			// MARK: - Member Types

			typedef Key																key_type;
			typedef T																mapped_type;
			typedef typename ft::pair<const Key, T>									value_type;
			typedef std::size_t														size_type;
			typedef std::ptrdiff_t													difference_type;
			typedef Compare															key_compare;
			typedef Allocator														allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef rbTree<value_type>												tree_type;
			typedef ft::node<value_type>											node_type;
			typedef typename Allocator::pointer										pointer;
			typedef typename Allocator::const_pointer								const_pointer;
			typedef ft::node_iterator<node_type*, value_type>						iterator;
			typedef ft::node_iterator<const node_type*, value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef typename allocator_type::template rebind<node_type>::other		allocator_rebind_node;
			typedef typename allocator_type::template rebind<tree_type>::other		allocator_rebind_tree;


			// MARK: - Member Class

			class value_compare : public std::binary_function<value_type, value_type, bool> {

				friend class map;

				protected:

					Compare	comp;
					value_compare( Compare c ) : comp( c ) {}

				public:

					typedef bool			result_type;
					typedef value_type		first_argument_type;
					typedef value_type		second_argument_type;

					result_type	operator () ( const first_argument_type &x, const second_argument_type &y ) const {
						return comp( x.first, y.first );
					}
			};

		
		private:

			allocator_type			_pair_alloc;
			allocator_rebind_node	_node_alloc;
			allocator_rebind_tree	_tree_alloc;
			key_compare				_comp;
			rbTree<value_type>*		_tree;

		
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

			map( const map &src ) : _pair_alloc( src._pair_alloc ), _comp( src._comp ) { 
				treeInit();
				copyTree( src._tree->root() );
			}


			// MARK: - Class Assignation Overload

			map	&operator = ( const map &src ) {
				if ( this != &src ) {
					_comp = src._comp;
					_pair_alloc = src._pair_alloc;
					burnTheTree( _tree->root() );
					treeInit();
					copyTree( src._tree->root() );
				}
				return *this;
			}


			// MARK: - Class Distructor

			~map( void ) {
				burnTheTree( _tree->root() );
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

			iterator				begin( void )			{ return _tree->begin(); }
			const_iterator			begin( void ) const		{ return _tree->begin(); }

			iterator				end( void )				{ return _tree->end(); }
			const_iterator			end( void ) const		{ return _tree->end(); }

			iterator				last( void )			{ return _tree->last(); }

			reverse_iterator		rbegin( void )			{ return --reverse_iterator( last() ); }
			const_reverse_iterator	rbegin( void ) const	{ return --const_reverse_iterator( last() ); }

			reverse_iterator		rend( void )			{ return reverse_iterator( iterator( _tree->end() ) ); }
			const_reverse_iterator	rend( void ) const		{ return const_reverse_iterator( iterator( _tree->end() ) ); }


			// MARK: - Capacity

			bool		empty( void ) const		{ return _tree->size() == 0; }
			size_type	size( void ) const		{ return _tree->size(); }
			size_type	max_size( void ) const	{ return (size_type)std::numeric_limits<difference_type>::max(); }


			// MARK: - Modifiers

			void	clear( void ) {
				burnTheTree( _tree->root() );
				treeInit();
			}

			ft::pair<iterator, bool>	insert( const value_type &value ) {
				return insertByHint( _tree->root(), value );
			}

			iterator	insert( iterator hint, const value_type &value ) {
				if ( hint == end() ) return insert( value ).first;
				
				if ( hint->first > value.first ) {
					iterator it = hint;
					--it;
					while ( !it.base()->isLeaf && it->first >= value.first )
						--hint; --it;
				} else if ( hint->first < value.first ) {
					iterator it = hint;
					++it;
					while ( !it.base()->isLeaf && it->first <= value.first )
						++hint; ++it;
				}
				return insertByHint( hint.base(), value ).first;	
			}

			template < class InputIt >
			void	insert( InputIt first, InputIt last ) {
				for ( ; first != last; ++first )
					insert( ft::make_pair( first->first, first->second ) );
			}

			void	erase( iterator pos ) {
				if ( !pos.base() || pos.base()->isLeaf ) return;
				node_type *upperNode = _tree->findNodeWithOneLeafOrMore( pos.base() );
				pos.base()->value = upperNode->value;
				
				_tree->deleteCheck( upperNode );
				// _node_alloc.destroy( upperNode );
				// _node_alloc.deallocate( upperNode, sizeof(node_type) );
				_tree->sizeDown();
			}

			void	erase( iterator first, iterator last ) {
				for ( ; first != last; ++first )
					erase( first );
			}

			size_type	erase( const key_type &key ) {
				iterator it = find( key );
				if ( it != end() ) {
					erase( it );
					return 1;
				}
				return 0;
			}

			void	swap( map &src ) {
				std::swap( _tree, src._tree );
			}


			// MARK: - Lookup

			size_type	count( const key_type &key ) const {
				return find( key ) == end() ? 0 : 1;
			}

			iterator	find( const key_type &key ) {
				node_type *tmp = _tree->root();

				while ( !tmp->isLeaf ) {
					if ( key == tmp->value->first )
						return iterator( tmp );
					else
						tmp = _comp( key, tmp->value->first ) ? tmp->left : tmp->right;
				}
				return end();
			}

			const_iterator	find( const key_type &key ) const {
				node_type *tmp = _tree->root();

				while ( !tmp->isLeaf ) {
					if ( key == tmp->value->first )
						return const_iterator( tmp );
					else
						tmp = _comp( key, tmp->value->first ) ? tmp->left : tmp->right;
				}
				return end();
			}

			size_type		size( void )	{ return _tree->size(); }

			iterator		lower_bound( const key_type &key )			{ return iterator( findLowerBound( key ) ); }
			const_iterator	lower_bound( const key_type &key ) const	{ return const_iterator( findLowerBound( key ) ); }

			iterator		upper_bound( const key_type &key )			{ return iterator( findUpperBound( key ) ); }
			const_iterator	upper_bound( const key_type &key ) const	{ return const_iterator( findUpperBound( key ) ); }

			ft::pair<iterator, iterator>	equal_range( const key_type &key ) {
				return ft::pair<iterator, iterator>( lower_bound( key ), upper_bound( key ) );
			}

			ft::pair<const_iterator, const_iterator>	equal_range( const key_type &key ) const {
				return ft::pair<const_iterator, const_iterator>( lower_bound( key ), upper_bound( key ) );
			}


			// MARK: - Observers

			key_compare	key_comp( void ) const	{ return _comp; }
			ft::map<key_type, mapped_type, key_compare, allocator_type>::value_compare	value_comp( void ) const { return value_compare( key_comp() ); }


			// MARK: - Non-Member Functions

			friend bool	operator == ( const map &lhs, const map &rhs ) {
				return lhs.size() == rhs.size() && ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
			}

			friend bool	operator != ( const map &lhs, const map &rhs ) {
				return !( lhs == rhs );
			}

			friend bool	operator < ( const map &lhs, const map &rhs ) {
				return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
			}

			friend bool	operator > ( const map &lhs, const map &rhs ) {
				return rhs < lhs;
			}

			friend bool	operator <= ( const map &lhs, const map &rhs ) {
				return !( rhs < lhs );
			}

			friend bool	operator >= ( const map &lhs, const map &rhs ) {
				return !( lhs < rhs );
			}


		private:

			void	burnTheTree( node_type *node ) {
				if ( !node || node->isLeaf ) return;
				if ( !node->left->isLeaf ) burnTheTree( node->left );
				if ( !node->right->isLeaf ) burnTheTree( node->right );
				_node_alloc.destroy( node );
				_node_alloc.deallocate( node, sizeof(node_type) );				
			}

			void	copyTree( node_type *node ) {
				if ( !node->left->isLeaf )
					copyTree( node->left );
				if ( !node->isLeaf )
					insert( *node->value );
				if ( !node->right->isLeaf )
					copyTree( node->right );
			}

			void	treeInit( void ) {
				_tree = _tree_alloc.allocate( sizeof(tree_type) );
				_tree_alloc.construct( _tree );
			}

			node_type	*nodeInit( node_type *parent ) {
				node_type	*node;

				node = _node_alloc.allocate( sizeof(node_type) );
				_node_alloc.construct( node );
				node->parent = parent;
				node->left = _tree->leaf();
				node->right = _tree->leaf();
				node->isLeaf = false;
				node->color = ( node->parent ) ? RED : BLACK;
				return node;
			}

			ft::pair<iterator, bool>	findPlace( node_type *hint, const value_type &value ) {
				if ( hint->isLeaf )
					return ft::make_pair( iterator(hint), true );

				node_type *node = hint;
				node_type *tmp;
				while ( !node->isLeaf ){
					if ( node->value->first == value.first ) return ft::make_pair( iterator(node), false );
					tmp = node;
					node = ( _comp( value.first, node->value->first ) )
						? node->left
						: node->right;
				}
				return ft::make_pair( iterator(tmp), true );
			}

			node_type	*findLowerBound( const key_type &key ) {
				iterator	it( _tree->root() );

				if ( _comp( it->first, key ) ) {
					++it;
					while ( _comp( it->first, key ) && it != end() )
						++it;
				} else if ( _comp( key, it->first ) ) {
					--it;
					while ( _comp( key, it->first ) && it != end() )
						--it;
				}
				return it.base();
			}

			node_type	*findUpperBound( const key_type &key ) {
				iterator	it( _tree->root() );

				if ( _comp( it->first, key ) ) {
					++it;
					while ( !_comp( key, it->first ) && it != end() )
						++it;
				} else if ( _comp( key, it->first ) ) {
					--it;
					while ( !_comp( it->first, key ) && it != end() )
						--it;
				}
				return it.base();
			}

			ft::pair<iterator, bool>	insertByHint( node_type *hint, const value_type &value ) {
				
				ft::pair<iterator, bool> place = findPlace( hint, value );
				if ( !place.second ) return place;
				if ( place.first.base()->isLeaf ) {
					_tree->setRoot( nodeInit( nullptr ) );
					_tree->root()->value = _pair_alloc.allocate( sizeof(value_type) );
					_pair_alloc.construct( _tree->root()->value, value );
					_tree->leaf()->left = _tree->root();
					_tree->leaf()->right = _tree->root();
					_tree->leaf()->parent = _tree->root();
					_tree->sizeUp();
					return ft::make_pair( iterator( _tree->root() ), true );
				}

				node_type	*parent = place.first.base();
				node_type	*new_node = nodeInit( parent );

				new_node->value = _pair_alloc.allocate( sizeof(value_type) );
				_pair_alloc.construct( new_node->value, value );

				if ( _comp( new_node->value->first, parent->value->first ) )
					parent->left = new_node;
				else
					parent->right = new_node;

				_tree->insertCheck( new_node );
				_tree->sizeUp();
				if ( _comp( value.first, _tree->leaf()->left->value->first ) ) {
					_tree->leaf()->left = new_node;
				} else if ( _comp( _tree->leaf()->right->value->first, value.first ) ) {
					_tree->leaf()->right = new_node;
				}

				return ft::make_pair( iterator( new_node ), true );
			}


	};

}

#endif
