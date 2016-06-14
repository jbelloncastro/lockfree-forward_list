
#ifndef FORWARD_LIST_NODE_H
#define FORWARD_LIST_NODE_H

#include <utility>

namespace ads {
namespace detail {

struct forward_list_node_base {
	typedef forward_list_node_base Node;

// Member functions
	forward_list_node_base() :
		_next(nullptr),
		_deleted( ATOMIC_FLAG_INIT )
	{
	}

	forward_list_node_base( forward_list_node_base* next ) :
		_next( next )
	{
	}

	Node* next() const noexcept
	{
		return _next.load();
	}

	void hook_node( Node* node )
	{
		Node* right;
		Node* middle = node;

		bool stable = false;
		do {
			right = _next;
			middle->_next = right;
		} while( !stable );
	}

	Node* unhook_next()
	{
		Node* to_delete;
		Node* new_right;

		bool stable = false;
		do {
			to_delete = _next;
			new_right = to_delete->_next;
			stable = _next.compare_exchange_weak( to_delete, new_right );
		} while( !stable );
		return to_delete;
	}

// Data members
	std::atomic<Node*> _next;
};

/**
 * @brief A base class for %forward_list.
 */
template< typename T >
struct forward_list_node : public forward_list_node_base {

// Member types
	typedef T&       reference;
	typedef const T& const_reference;
	typedef T*       pointer;
	typedef const T* const_pointer;

// Member functions
	forward_list_node() = delete;

	forward_list_node( const forward_list_node& ) = delete;

	forward_list_node( forward_list_node&& other ) :
		forward_list_node_base( std::forward( other ) ),
		_value( std::move( other._value ) )
	{
	}

	forward_list_node( const_reference value ) :
		forward_list_node_base(),
		_value( value )
	{
	}

	template < typename... Args >
	forward_list_node( Args&&... args ) :
		forward_list_node_base(),
		_value( std::forward<Args>(args)... )
	{
	}

	pointer valuePtr()
	{
		return &_value;
	}

	const_pointer valuePtr() const
	{
		return &_value;
	}

// Member elements
	T     _value;
};

} // namespace detail
} // namespace ads

#endif // FORWARD_LIST_NODE_H

