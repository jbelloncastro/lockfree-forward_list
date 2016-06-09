
#ifndef FORWARD_LIST_BASE_H
#define FORWARD_LIST_BASE_H

#include "forward_list_iterator.hpp"
#include "forward_list_node.hpp"

#include <memory>
#include <utility>

namespace ads {
namespace detail {

/**
 * @brief A helper basic node class for %forward_list.
 */
template<
	class T,
	class Allocator
	>
struct forward_list_base {
// Member types
	typedef forward_list_node<T>                                       Node;
	typedef forward_list_node_base                                     Node_base;

	typedef typename Allocator::template rebind<T>::other              value_alloc_type;
	typedef typename Allocator::template rebind<Node>::other           node_alloc_type;
	typedef typename std::allocator_traits<node_alloc_type>            node_alloc_traits;
	typedef typename std::allocator_traits<node_alloc_type>::size_type size_type;

	typedef forward_list_iterator<T>                                   iterator;
	typedef forward_list_const_iterator<T>                             const_iterator;

// Member functions
	protected:
		/**
		 * \brief allocates uninitialized storage using the allocator 
		 * the amount of reserved storage is enough to hold a node
		 */
		Node* get_node()
		{
			Node* new_node = node_alloc_traits::allocate( _allocator, 1 );
			return std::addressof(*new_node);
		}

		/**
		 * \brief deallocates uninitialized storage using the allocator 
		 */
		void put_node( Node* p )
		{
			typedef typename node_alloc_traits::pointer ptr_t;
			auto ptr = std::pointer_traits<ptr_t>::pointer_to( *p );
			node_alloc_traits::deallocate( _allocator, ptr, 1 );
		}

		/**
		 * \brief constructs a new node
		 */
		template< typename... Args >
		Node* create_node( Args&&... args )
		{
			Node* new_node = get_node();
			try {
				node_alloc_traits::construct( _allocator, new_node, std::forward<Args>(args)... );
			} catch( ... ) {
				put_node( new_node );
				throw;// throw exception again
			}
		}

	public:
		explicit forward_list_base( const node_alloc_type& allocator ) :
			_allocator( allocator ),
			_head()
		{
		}

		forward_list_base( const forward_list_base& other );

		forward_list_base( const forward_list_base& other, const node_alloc_type& allocator );

		forward_list_base( forward_list_base&& other ) :
			_allocator( std::move( other._allocator ) ),
			_head()
		{
			_head._next = other._head._next;
			other._head._next = nullptr;
		}

		forward_list_base( forward_list_base&& other, const node_alloc_type& a );

		~forward_list_base()
		{
			erase_after( &_head, nullptr );
		}

		Node* erase_after( Node_base* position )
		{
			// Update position's next pointer
			Node* current = static_cast<Node*>(position->_next);
			position->_next = current->_next;
			// Release position's next node
			node_alloc_traits::destroy( _allocator, std::addressof( current->_value ) );
			current->~Node();
			put_node( current );
			// Return next element
			return position->_next;
		}

		Node* erase_after( Node_base* position, Node_base* last )
		{
			Node* current = static_cast<Node*>(position->_next);
			while( current != last ) {
				// Update current node
				Node* temp = current;
				current = static_cast<Node*>(current->_next);
				// Release node
				node_alloc_traits::destroy( _allocator, std::addressof( temp->_value ) );
				temp->~Node();
				put_node( temp );
			}
			position->_next = last;
		}

		template < typename... Args >
		Node* insert_after( const_iterator position, Args&&... args )
		{
			Node_base* to = position._node;
			// Create new node
			Node* new_node = create_node( std::forward<Args>(args)... );
			new_node->_next = position._node->_next;
			// Update node's next position with the new node
			position._node->_next = new_node;
			return static_cast<Node*>(to->_next);
		}

		template< typename InputIterator >
		void range_initialize( InputIterator first, InputIterator last )
		{
			Node_base* to = &_head;
			for( ; first != last; ++first )
			{
				to->_next = create_node( *first );
				to = to->_next;
			}
		}

		void fill_initialize( size_type n, const T& value )
		{
			Node_base* to = &_head;
			for( ; n > 0; n-- ) {
				to->_next = create_node( value );
				to = to->_next;
			}
		}

		void default_initialize( size_type n )
		{
			Node_base* to = &_head;
			for( ; n > 0; n-- ) {
				to->_next = create_node();
				to = to->_next;
			}
		}

	// Data members
		node_alloc_type        _allocator;
		forward_list_node_base _head;
};

} // namespace detail
} // namespace ads

#endif // FORWARD_LIST_BASE_H

