
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
class forward_list_iterator : public iterator< std::forward_iterator_tag, T >
{
	private:
// Member types
		typedef typename forward_list_node<T,Allocator> node;

// Member attributes
		node* _current_pos;

	public:
// Member functions
		forward_list_iterator() :
			_current_pos( nullptr )
		{
		}

		explicit forward_list_iterator( node* position ) :
			_current_pos( position )
		{
		}

		forward_list_iterator( const forward_list_iterator& other ) :
			_current_pos( other._current_pos )
		{
		}

		bool operator==( const forward_list_iterator& other )
		{
			return _current_pos == other._current_pos;
		}

		bool operator!=( const forward_list_iterator& other )
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

		forward_list_iterator& operator++() noexcept
		{
			_current_pos = _current_pos->_next;
			return *this;
		}

		forward_list_iterator operator++(int) noexcept
		{
			forward_list_iterator_iterator tmp = *this;
			_current_pos = _current_pos->_next;
			return tmp;
		}
};

template<
	typename T,
	typename Allocator
	>
class forward_list_const_iterator : public iterator< std::forward_iterator_tag, T >
{

}:

} // namespace detail
} // namespace ads

#endif // FORWARD_ALLOCATOR_H

