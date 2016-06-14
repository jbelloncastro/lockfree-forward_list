
#ifndef FORWARD_ALLOCATOR_H
#define FORWARD_ALLOCATOR_H

#include "forward_list_node.hpp"

#include <iterator>
#include <memory>

namespace ads {
namespace detail {

template< typename T >
struct forward_list_iterator : public std::iterator< std::forward_iterator_tag, T >
{
// Member types
		typedef forward_list_iterator<T> self_type;
		typedef forward_list_node_base   node_base_type;
		typedef forward_list_node<T>     node_type;
		typedef node_base_type*          node_pointer;

		typedef T&                       reference;
		typedef T*                       pointer;

// Member attributes
		node_pointer _node;

// Member functions
		forward_list_iterator() :
			_node()
		{
		}

		explicit forward_list_iterator( node_pointer position ) :
			_node( position )
		{
		}

		bool operator==( const self_type& other ) const noexcept
		{
			return _node == other._node;
		}

		bool operator!=( const self_type& other ) const noexcept
		{
			return _node != other._node;
		}

		reference operator*() const noexcept
		{
			return *static_cast<node_type*>(_node)->valuePtr();
		}

		pointer operator->() const noexcept
		{
			return static_cast<node_type*>(_node)->valuePtr();
		}

		// ++it
		self_type& operator++() noexcept
		{
			_node = _node->next();
			return *this;
		}

		// it++
		self_type operator++(int) noexcept
		{
			self_type tmp = *this;
			_node = _node->next();
			return tmp;
		}

		self_type next() const noexcept
		{
			if( _node )
				return forward_list_iterator( _node->next() );
			else
				return forward_list_iterator( nullptr );
		}
};

template< typename T >
struct forward_list_const_iterator : public std::iterator< std::forward_iterator_tag, T >
{
// Member types
		typedef forward_list_const_iterator<T> self_type;
		typedef forward_list_iterator<T>       iterator;
		typedef forward_list_node_base         node_base_type;
		typedef forward_list_node<T>           node_type;
		typedef node_base_type*                node_pointer;

		typedef const T&                             const_reference;
		typedef const T*                             const_pointer;

// Member attributes
		node_pointer _node;

// Member functions
		forward_list_const_iterator() :
			_node()
		{
		}

		explicit forward_list_const_iterator( node_pointer position ) :
			_node( position )
		{
		}

		// Implicit conversion
		forward_list_const_iterator( const iterator& other ) :
			_node( other._node )
		{
		}

		bool operator==( const self_type& other ) const noexcept
		{
			return _node == other._node;
		}

		bool operator!=( const self_type& other ) const noexcept
		{
			return _node != other._node;
		}

		const_reference operator*() const noexcept
		{
			return *static_cast<node_type*>(_node)->valuePtr();
		}

		const_pointer operator->() const noexcept
		{
			return static_cast<node_type*>(_node)->valuePtr();
		}

		// ++it
		self_type& operator++() noexcept
		{
			_node = _node->next();
			return *this;
		}

		// it++
		self_type operator++(int) noexcept
		{
			self_type tmp = *this;
			_node = _node->next();
			return tmp;
		}

		self_type next() const noexcept
		{
			if( _node )
				return forward_list_const_iterator( _node->next() );
			else
				return forward_list_const_iterator( nullptr );
		}
};

template < typename T >
inline bool operator==( const forward_list_iterator<T>& lhs, const forward_list_const_iterator<T>& rhs )
{
	return lhs._node == rhs._node;
}

template < typename T >
inline bool operator!=( const forward_list_iterator<T>& lhs, const forward_list_const_iterator<T>& rhs )
{
	return lhs._node != rhs._node;
}

} // namespace detail
} // namespace ads

#endif // FORWARD_ALLOCATOR_H

