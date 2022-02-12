#ifndef SET_HPP
# define SET_HPP

#include <iostream>
#include "../iterators/node_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/node.hpp"
#include "../utils/tree.hpp"
# include "../utils/equal.hpp"
# include "../utils/lexicographical_compare.hpp"

namespace ft {

	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set {

		public:

			// MARK: - Member types

			typedef Key														key_type;
			typedef Key														value_type;
			typedef ft::node<value_type>									node_type;
			typedef ft::rbTree<value_type>									tree_type;
			typedef std::size_t												size_type;
			typedef std::ptrdiff_t											difference_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Allocator												allocator_type;
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			typedef typename Allocator::pointer								pointer;
			typedef typename Allocator::const_pointer						const_pointer;
			typedef ft::node_iterator< node_type*, value_type >				iterator;
			typedef ft::node_iterator< const node_type*, value_type >		const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename Allocator::template rebind<node_type>::other	allocator_rebind_node;
			typedef typename Allocator::template rebind<tree_type>::other	allocator_rebind_tree;

		
		private:

			allocator_type			_allocator;
			allocator_rebind_node	_node_allocator;
			allocator_rebind_tree	_tree_allocator;
			value_compare			_comp;
			tree_type*				_tree;

		
		public:


			// MARK: - Class Constructors

			set( void ) { treeInit(); }

			explicit set( const Compare &comp, const Allocator &alloc = Allocator() ) : _comp( comp ), _allocator( alloc ) { treeInit(); }

			template< class InputIt >
			set( InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator() ) : _comp( comp ), _allocator( alloc ) {
				treeInit();
				for ( ; first != last; ++first )
					insert( *first );
			}

			
			// MARK: - Class Copy Constructor

			set( const set &src ) {
				treeInit();
				copyTree( src._tree->root() );
			}


			// MARK: - Assignation Overload

			set	&operator = ( const set &src ) {
				if ( this != &src ) {
					_comp = src._comp;
					_allocator = src._allocator;
					clear();
					copyTree( src._tree->root() );
				}
				return *this;
			}


			// MARK: - Class Distructor

			~set( void ) {
				destroySet( _tree->root() );
				_tree_allocator.destroy( _tree );
				_tree_allocator.deallocate( _tree, sizeof( tree_type ) );
			}


			// MARK: - Getters

			allocator_type	get_allocator( void ) const	{ return _allocator; }


			// MARK: - Iterators

			iterator				begin( void )			{ return _tree->getBegin(); }
			const_iterator			begin( void ) const		{ return _tree->getBegin(); }
			iterator				end( void )				{ return _tree->end(); }
			const_iterator			end( void ) const		{ return _tree->end(); }
			reverse_iterator		rbegin( void )			{ return reverse_iterator( iterator( _tree->getLast() ) ); }
			const_reverse_iterator	rbegin( void ) const	{ return const_reverse_iterator( const_iterator( _tree->getLast() ) ); }
			reverse_iterator		rend( void )			{ return reverse_iterator( iterator( _tree->end() ) ); }
			const_reverse_iterator	rend( void ) const		{ return const_reverse_iterator( const_iterator( _tree->end() ) ); }


			// MARK: - Capacity

			bool		empty( void ) const	{ return size() == 0; }
			size_type	size( void ) const	{ return _tree->size(); }
			size_type	max_size( void ) const	{ return (size_type)std::numeric_limits<difference_type>::max(); }


			// MARK: - Modifiers

			void	clear( void ) {
				destroySet( _tree->root() );
				_tree_allocator.destroy( _tree );
				_tree_allocator.deallocate( _tree, sizeof( tree_type ) );
				treeInit();
			}


			// MARK: - Insert

			ft::pair<iterator, bool>	insert( const value_type &value ) {
				return insertByHint( _tree->root(), value );
			}

			iterator	insert( iterator hint, const value_type &value ) {
				if ( hint == end() ) return insert( value ).first;
				
				if ( _comp( value, *hint ) ) {
					iterator it = hint;
					--it;
					while ( !it.base()->isLeaf && _comp( *it, value ) )
						--hint; --it;
				} else if ( _comp( *hint, value ) ) {
					iterator it = hint;
					++it;
					while ( !it.base()->isLeaf && !_comp( value, *it ) )
						++hint; ++it;
				}
				return insertByHint( hint.base(), value ).first;	
			}

			template < class InputIt >
			void	insert( InputIt first, InputIt last ) {
				for ( ; first != last; ++first )
					insert( *first );
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

			void	swap( set &src ) {
				std::swap( _tree, src._tree );
			}


			// MARK: - Lookup

			size_type	count( const Key &key ) const {
				return find( key ) == end() ? 0 : 1;
			}

			iterator	find( const Key &key ) {
				node_type *tmp = _tree->root();

				while ( !tmp->isLeaf ) {
					if ( key == *tmp->value )
						return iterator( tmp );
					else
						tmp = _comp( key, *tmp->value ) ? tmp->left : tmp->right;
				}
				return end();
			}

			const_iterator	find( const Key &key ) const {
				node_type *tmp = _tree->root();

				while ( !tmp->isLeaf ) {
					if ( key == *tmp->value )
						return const_iterator( tmp );
					else
						tmp = _comp( key, *tmp->value ) ? tmp->left : tmp->right;
				}
				return end();
			}

			iterator		lower_bound( const Key &key )		{ return findBound( key ); }
			const_iterator	lower_bound( const Key &key ) const	{ return findBound( key ); }

			iterator		upper_bound( const Key &key ) {
				iterator tmp = lower_bound( key );
				if ( tmp == end() )
					return tmp;
				else {
					if ( _comp( key, *tmp ) )
						return tmp;
					return ++tmp;
				}
			}

			const_iterator		upper_bound( const Key &key ) const {
				const_iterator tmp = lower_bound( key );
				if ( tmp == end() )
					return tmp;
				else {
					if ( _comp( key, *tmp ) )
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

			key_compare			key_comp( void ) const		{ return _comp; }
			set::value_compare	value_comp( void ) const	{ return _comp; }


			// MARK: - Non-Member Functions

			friend bool	operator == ( const set &lhs, const set &rhs ) {
				return lhs.size() == rhs.size() && ft::equal( lhs.begin(), lhs.end(), rhs.begin() );
			}

			friend bool	operator != ( const set &lhs, const set &rhs ) {
				return !( lhs == rhs );
			}

			friend bool	operator < ( const set &lhs, const set &rhs ) {
				return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
			}

			friend bool	operator > ( const set &lhs, const set &rhs ) {
				return rhs < lhs;
			}

			friend bool	operator <= ( const set &lhs, const set &rhs ) {
				return !( rhs < lhs );
			}

			friend bool	operator >= ( const set &lhs, const set &rhs ) {
				return !( lhs < rhs );
			}


		private:

			void	treeInit( void ) {
				_tree = _tree_allocator.allocate( sizeof( tree_type ) );
				_tree_allocator.construct( _tree );
			}

			void	copyTree( node_type *node ) {
				if ( !node->left->isLeaf )
					copyTree( node->left );
				if ( !node->isLeaf )
					insert( *node->value );
				if ( !node->right->isLeaf )
					copyTree( node->right );
			}

			void	destroySet( node_type *node ) {
				if ( !node || node->isLeaf ) return;
				if ( !node->left->isLeaf ) destroySet( node->left );
				if ( !node->right->isLeaf ) destroySet( node->right );
				_node_allocator.destroy( node );
				_node_allocator.deallocate( node, sizeof(node_type) );
				_tree->sizeDown();				
			}

			node_type	*nodeInit( node_type *parent, const value_type &value = value_type() ) {
				node_type	*node;

				node = _node_allocator.allocate( sizeof(node_type) );
				_node_allocator.construct( node, value );
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
					if ( *hint->value == value ) return ft::make_pair( hint, false );
					parent = hint;
					hint = ( _comp( value, *hint->value ) )
						? hint->left
						: hint->right;
				}
				return ft::make_pair( parent, true );
			}

			ft::pair<iterator, bool>	insertByHint( node_type *hint, const value_type &value ) {

				node_type					*new_node;
				ft::pair<node_type*, bool>	result = findParent( hint, value );

				if ( !result.second ) return ft::make_pair( result.first, false );
				new_node = nodeInit( result.first, value );

				if ( result.first )
					if ( _comp( value, *result.first->value ) )	result.first->left = new_node;
					else result.first->right = new_node;
				else
					_tree->setRoot( new_node );

				_tree->insertCheck( new_node );

				if ( _comp( value, *_tree->leaf()->left->value ) )
					_tree->leaf()->left = new_node;
				else if ( _comp( *_tree->leaf()->right->value, value ) )
					_tree->leaf()->right = new_node;
				
				_tree->sizeUp();
				return ft::make_pair( new_node, true );
			}

			iterator	findBound( const key_type &key ) {
				node_type	*tmp = _tree->root();

				while ( !tmp->isLeaf ) {
					if ( key == *tmp->value )
						return iterator( tmp );
					else {
						if ( _comp( key, *tmp->value ) ) {
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
					if ( key == *tmp->value )
						return const_iterator( tmp );
					else {
						if ( _comp( key, *tmp->value ) ) {
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
	};
}


#endif
