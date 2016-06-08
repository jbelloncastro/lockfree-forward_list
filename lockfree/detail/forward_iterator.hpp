
#ifndef FORWARD_ALLOCATOR_H
#define FORWARD_ALLOCATOR_H

#include "forward_list_node.hpp"

#include <memory>

namespace ads {
namespace detail {

template<
	typename T,
	typename Allocator
	>
struct forward_list_iterator : public std::iterator< std::forward_iterator_tag, T >
{
	private:
// Member types
		typedef typename forward_list_const_iterator<T, Allocator> self_type;
		typedef typename forward_list_node<T,Allocator> node;
		typedef node* node_pointer;

// Member attributes
		node_pointer _current_pos;

	public:
// Member functions
		forward_list_iterator() :
			_current_pos()
		{
		}

		explicit forward_list_iterator( node_pointer position ) :
			_current_pos( position )
		{
		}

		bool operator==( const self_type& other ) const noexcept
		{
			return _current_pos == other._current_pos;
		}

		bool operator!=( const self_type& other ) const noexcept
		{
			return _current_pos != other._current_pos;
		}

		reference operator*() const noexcept
		{
			return *_current_pos->valuePtr();
		}

		pointer operator->() const noexcept
		{
			return _current_pos->valuePtr();
		}

		// ++it
		self_type& operator++() noexcept
		{
			_current_pos = _current_pos->next();
			return *this;
		}

		// it++
		self_type operator++(int) noexcept
		{
			self_type tmp = *this;
			_current_pos = _current_pos->next();
			return tmp;
		}
};

template<
	typename T,
	typename Allocator
	>
class forward_list_const_iterator : public iterator< std::forward_iterator_tag, T >
{
	private:
// Member types
		typedef typename forward_list_const_iterator<T, Allocator> self_type;
		typedef typename forward_list_iterator<T, Allocator> iterator;
		typedef typename forward_list_node<T,Allocator> node;
		typedef node* node_pointer;

// Member attributes
		node_pointer _current_pos;

	public:
// Member functions
		forward_list_iterator() :
			_current_pos()
		{
		}

		explicit forward_list_iterator( node_pointer position ) :
			_current_pos( position )
		{
		}

		// Implicit conversion
		forward_list_iterator( const iterator& other ) :
			_current_pos( other._current_pos )
		{
		}

		bool operator==( const self_type& other ) const noexcept
		{
			return _current_pos == other._current_pos;
		}

		bool operator!=( const self_type& other ) const noexcept
		{
			return _current_pos != other._current_pos;
		}

		reference operator*() const noexcept
		{
			return *_current_pos->valuePtr();
		}

		pointer operator->() const noexcept
		{
			return _current_pos->valuePtr();
		}

		// ++it
		self_type& operator++() noexcept
		{
			_current_pos = _current_pos->next();
			return *this;
		}

		// it++
		self_type operator++(int) noexcept
		{
			self_type tmp = *this;
			_current_pos = _current_pos->next();
			return tmp;
		}
}:

} // namespace detail
} // namespace ads

#endif // FORWARD_ALLOCATOR_H

