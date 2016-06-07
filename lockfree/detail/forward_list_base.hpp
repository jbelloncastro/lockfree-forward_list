
#ifdef FORWARD_LIST_BASE_H
#define FORWARD_LIST_BASE_H

#include "forward_list_node.hpp"

namespace ads {
namespace detail {

/**
 * @brief A helper basic node class for %forward_list.
 */
template<
	class T,
	class Allocator
	>
class forward_list_base<T,Allocator> {
	protected:
// Member types
		class node;
		class forward_iterator;

		typedef typename Allocator::template rebind<T>    value_alloc_type;
		typedef typename Allocator::template rebind<node> node_alloc_type;
		typedef typename std::allocator_traits<node_allocator_type> node_alloc_traits;

// Member functions
		explicit forward_list_base( const node_alloc_type& allocator ) :
			_allocator( allocator ),
			_head(nullptr)
		{
		}

		forward_list_base( const forward_list_base& other );

		forward_list_base( const forward_list_base& other, const node_alloc_type& allocator );

		forward_list_base( forward_list_base&& other ) :
			_head( other._head )
		{
			other._head(nullptr)
		}

		forward_list_base( forward_list_base&& other, const node_alloc_type& a );

		~forward_list_base()
		{
			erase_after( _head, nullptr );
		}

		/**
		 * \brief allocates uninitialized storage using the allocator 
		 * the amount of reserved storage is enough to hold a node
		 */
		node* get_node()
		{
			node* _node = node_alloc_traits::allocate( _allocator, 1 );
			return std::addressof(*node);
		}

		/**
		 * \brief deallocates uninitialized storage using the allocator 
		 */
		void put_node( node* p )
		{
			typedef typename node_alloc_traits::pointer ptr_t;
			auto ptr = std::pointer_traits<ptr_t>::pointer_to( *p );
			node_alloc_traits::deallocate( _allocator, ptr, 1 );
		}

		/**
		 * \brief constructs a new node
		 */
		template< typename... Args >
		node* create_node( Args&&... args )
		{
			node* new_node = get_node();
			try {
				node_alloc_traits::construct( _allocator, new_node, std::forward(args)... );
			} catch( ... ) {
				put_node( new_node );
			}
		}

		node* erase_after( node* position )
		{
			// Update position's next pointer
			node* current = position->_next;
			position->_next = current->_next;
			// Release position's next node
			allocator_traits::destroy( _allocator, std::addressof( current->_value ) );
			current->~node();
			put_node( current );
			// Return next element
			return position->_next;
		}

		node* erase_after( node* position, node* last )
		{
			node* current = position->_next;
			while( current != last ) {
				// Update current node
				node* temp = current;
				current = current->_next;
				// Release node
				allocator_traits::destroy( _allocator, std::addressof( temp->_value ) );
				temp->~node();
				put_node( temp );
			}
			position->_next = last;
		}

		template < typename... Args >
		node* insert_after( const_iterator position, Args&&... args )
		{
			node* to = position._node;
			// Create new node
			node* new_node = create_node( std::forward(args)... );
			new_node->_next = position->_next;
			// Update node's next position with the new node
			position->_next = new_node;
			return to->_next;
		}

	private:
		node_allocator_type _allocator;
		node*               _head;
};

} // namespace detail
} // namespace ads

#endif // FORWARD_LIST_NODE_H

