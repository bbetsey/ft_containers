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
			typedef ft::node<value_type>														node_type;
			typedef std::size_t																	size_type;
			typedef std::ptrdiff_t																difference_type;
			typedef Compare																		key_compare;
			typedef Allocator																	allocator_type;
			typedef value_type&																	reference;
			typedef const value_type&															const_reference;
			typedef typename Allocator::pointer													pointer;
			typedef typename Allocator::const_pointer											const_pointer;
			typedef ft::node_iterator<node_type*, value_type>									iterator;
			typedef ft::node_iterator<const node_type*, value_type>								const_iterator;
			typedef ft::reverse_iterator<iterator>												reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>										const_reverse_iterator;
			typedef typename allocator_type::template rebind<ft::node<value_type> >::other		allocator_rebind_node;
			typedef typename allocator_type::template rebind<ft::rbTree<value_type> >::other	allocator_rebind_tree;
			

			// MARK: - Member Class

			class value_compare : public std::binary_function<value_type, value_type, bool> {

				friend class map;

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

			typedef rbTree<value_type, value_compare>											tree_type;

		
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

			iterator		begin( void )		{ return _tree->begin(); }
			const_iterator	begin( void ) const	{ return _tree->begin(); }

			iterator		end( void )			{ return _tree->end(); }
			const_iterator	end( void ) const	{ return _tree->end(); }

			reverse_iterator		rbegin( void )			{ return reverse_iterator( iterator( _tree->last() ) ); }
			const_reverse_iterator	rbegin( void ) const	{ return const_reverse_iterator( iterator( _tree->last() ) ); }

			reverse_iterator		rend( void )			{ return reverse_iterator( iterator( _tree->end() ) ); }
			const_reverse_iterator	rend( void ) const		{ return const_reverse_iterator( iterator( _tree->end() ) ); }


			// MARK: - Capacity

			bool		empty( void ) const	{ return _tree->size() == 0; }
			size_type	size( void ) const	{ return _tree->size(); }
			size_type	max_size( void ) const { return (size_type)std::numeric_limits<difference_type>::max(); }


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

				if ( !pos.base()->hasOneOrMoreLeaf() ) {
					pos = pos.base()->right;
					while ( !pos.base()->left->isLeaf )
						pos = iterator( pos.base()->left );
				}

				_tree->deleteCheck( pos.base() );
				_node_alloc.destroy( pos.base() );
				_node_alloc.deallocate( pos.base(), sizeof(node_type) );
				_tree->sizeDown();
			}

			void	erase( iterator first, iterator last ) {
				for ( ; first != last; ++first )
					erase( first );
			}

			size_type	erase( const key_type &key ) {
				iterator it = find( key );
				if ( it.base() ) {
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

			size_type	size( void )	{ return _tree->size(); }


			// Проработать ситуацию когда текущего ключа нет в дереве

			iterator	lower_bound( const key_type &key ) {
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
				return it == end() ? it : --it;
			}

			iterator	upper_bound( const key_type &key ) {
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
				return it == end() ? it : ++it;
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
				_tree->setRoot( leafInit( nullptr ) );
			}

			node_type	*leafInit( node_type *parent ) {
				node_type	*node;

				node = _node_alloc.allocate( sizeof(node_type) );
				_node_alloc.construct( node );
				node->parent = parent;
				return node;
			}

			ft::pair<iterator, bool>	findPlace( node_type *hint, const value_type &value ) {
				node_type *node = hint;
				while ( !node->isLeaf ){
					if ( node->value->first == value.first ) return ft::make_pair( iterator(node), false );
					node = ( _comp( value.first, node->value->first ) )
						? node->left
						: node->right;
				}
				return ft::make_pair( iterator(node), true );
			}

			ft::pair<iterator, bool>	insertByHint( node_type *hint, const value_type &value ) {
				ft::pair<iterator, bool> place = findPlace( hint, value );
				if ( !place.second ) return place;
				
				node_type	*node = place.first.base();
				node->value = _pair_alloc.allocate( sizeof(value_type) );
				_pair_alloc.construct( node->value, value );
				node->right = leafInit( node );
				node->left = leafInit( node );
				node->isLeaf = false;
				node->color = ( node->parent ) ? RED : BLACK;

				_tree->insertCheck( node );
				_tree->sizeUp();

				return place;
			}
			

	};

}

#endif
