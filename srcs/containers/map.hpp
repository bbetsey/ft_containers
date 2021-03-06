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
					clear();
					copyTree( src._tree->root() );
				}
				return *this;
			}


			// MARK: - Class Distructor

			~map( void ) {
				burnTheTree( _tree->root() );
				_tree_alloc.destroy( _tree );
				_tree_alloc.deallocate( _tree, sizeof( tree_type ) );
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

			mapped_type	&operator [] ( const key_type &key ){ return insert( ft::make_pair( key, mapped_type() ) ).first->second; }


			// MARK: - Iterators

			iterator				begin( void )			{ return _tree->getBegin(); }
			const_iterator			begin( void ) const		{ return _tree->getBegin(); }

			iterator				end( void )				{ return _tree->end(); }
			const_iterator			end( void ) const		{ return _tree->end(); }

			iterator				last( void )			{ return _tree->getLast(); }

			reverse_iterator		rbegin( void )			{ return reverse_iterator( last() ); }
			const_reverse_iterator	rbegin( void ) const	{ return const_reverse_iterator( last() ); }

			reverse_iterator		rend( void )			{ return reverse_iterator( iterator( _tree->end() ) ); }
			const_reverse_iterator	rend( void ) const		{ return const_reverse_iterator( iterator( _tree->end() ) ); }


			// MARK: - Capacity

			bool		empty( void ) const		{ return _tree->size() == 0; }
			size_type	size( void ) const		{ return _tree->size(); }
			size_type	max_size( void ) const	{ return (size_type)std::numeric_limits<difference_type>::max(); }


			// MARK: - Modifiers

			void	clear( void ) {
				burnTheTree( _tree->root() );
				_tree_alloc.destroy( _tree );
				_tree_alloc.deallocate( _tree, sizeof( tree_type ) );
				treeInit();
			}


			// MARK: - Insert

			ft::pair<iterator, bool>	insert( const value_type &value ) {
				return insertByHint( _tree->root(), value );
			}

			iterator	insert( iterator hint, const value_type &value ) {
				if ( hint == end() ) return insert( value ).first;
				
				if ( _comp( value.first, hint->first ) ) {
					iterator it = hint;
					--it;
					while ( !it.base()->isLeaf && _comp( it->first, value.first ) )
						--hint; --it;
				} else if ( _comp( hint->first, value.first ) ) {
					iterator it = hint;
					++it;
					while ( !it.base()->isLeaf && !_comp( value.first, it->first ) )
						++hint; ++it;
				}
				return insertByHint( hint.base(), value ).first;	
			}

			template < class InputIt >
			void	insert( InputIt first, InputIt last ) {
				for ( ; first != last; ++first )
					insert( ft::make_pair( first->first, first->second ) );
			}


			// MARK: - Erase

			void	erase( iterator pos ) {
				iterator tmp = pos;
				_tree->nodeDelete( tmp.base() );
			}

			void	erase( iterator first, iterator last ) {
				iterator	tmp;
				for ( ; first != last; ) {
					tmp = first++;
					erase( tmp );
				}
			}

			size_type	erase( const key_type &key ) {
				iterator it = find( key );
				if ( it != end() ) {
					erase( it );
					return 1;
				}
				return 0;
			}


			// MARK: - Swap

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

			iterator		lower_bound( const key_type &key )			{ return findBound( key ); }
			const_iterator	lower_bound( const key_type &key ) const	{ return findBound( key ); }

			iterator		upper_bound( const key_type &key ) {
				iterator tmp = lower_bound( key );
				if ( tmp == end() )
					return tmp;
				else {
					if ( _comp( key, tmp->first ) )
						return tmp;
					return ++tmp;
				}
			}

			const_iterator		upper_bound( const key_type &key ) const {
				const_iterator tmp = lower_bound( key );
				if ( tmp == end() )
					return tmp;
				else {
					if ( _comp( key, tmp->first ) )
						return tmp;
					return ++tmp;
				}
			}

			ft::pair<iterator, iterator>	equal_range( const key_type &key ) {
				return ft::make_pair( lower_bound( key ), upper_bound( key ) );
			}

			ft::pair<const_iterator, const_iterator>	equal_range( const key_type &key ) const {
				return ft::make_pair( lower_bound( key ), upper_bound( key ) );
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
				_tree->sizeDown();				
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

			node_type	*nodeInit( node_type *parent, const value_type &value = value_type() ) {
				node_type	*node;

				node = _node_alloc.allocate( sizeof(node_type) );
				_node_alloc.construct( node, value );
				node->parent = parent;
				node->left = _tree->leaf();
				node->right = _tree->leaf();
				node->isLeaf = false;
				node->color = RED;
				return node;
			}

			ft::pair<node_type*, bool>	findParent( node_type *hint, const value_type &value ) {

				node_type *parent = NULL;
				while ( !hint->isLeaf ) {
					if ( hint->value->first == value.first ) return ft::make_pair( hint, false );
					parent = hint;
					hint = ( _comp( value.first, hint->value->first ) )
						? hint->left
						: hint->right;
				}
				return ft::make_pair( parent, true );
			}

			iterator	findBound( const key_type &key ) {
				node_type	*tmp = _tree->root();

				while ( !tmp->isLeaf ) {
					if ( key == tmp->value->first )
						return iterator( tmp );
					else {
						if ( _comp( key, tmp->value->first ) ) {
							if ( !tmp->left->isLeaf )
								tmp = tmp->left;
							else
								return iterator( tmp );
						} else {
							if ( !tmp->right->isLeaf )
								tmp = tmp->right;
							else
								return ++iterator( tmp );
						}
					}
				}
				return end();
			}

			const_iterator	findBound( const key_type &key ) const {
				node_type	*tmp = _tree->root();

				while ( !tmp->isLeaf ) {
					if ( key == tmp->value.first )
						return const_iterator( tmp );
					else {
						if ( _comp( key, tmp->value.first ) ) {
							if ( !tmp->left->isLeaf )
								tmp = tmp->left;
							else
								return const_iterator( tmp );
						} else {
							if ( !tmp->right->isLeaf )
								tmp = tmp->right;
							else
								return ++const_iterator( tmp );
						}
					}
				}
				return end();
			}

			ft::pair<iterator, bool>	insertByHint( node_type *hint, const value_type &value ) {

				node_type					*new_node;
				ft::pair<node_type*, bool>	result = findParent( hint, value );

				if ( !result.second ) return ft::make_pair( result.first, false );
				new_node = nodeInit( result.first, value );

				if ( result.first )
					if ( _comp( value.first, result.first->value->first ) )	result.first->left = new_node;
					else result.first->right = new_node;
				else
					_tree->setRoot( new_node );

				_tree->insertCheck( new_node );

				if ( _comp( value.first, _tree->leaf()->left->value->first ) )
					_tree->leaf()->left = new_node;
				else if ( _comp( _tree->leaf()->right->value->first, value.first ) )
					_tree->leaf()->right = new_node;
				
				_tree->sizeUp();
				return ft::make_pair( new_node, true );
			}


	};

}

#endif
