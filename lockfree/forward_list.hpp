
#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "detail/forward_list_base.hpp"
#include "detail/forward_list_iterator.hpp"

#include <memory>

namespace ads {

template<
	class T,
	class Allocator = std::allocator<T>
	>
class forward_list {
// Member types
	private:
		typedef detail::forward_list_base<T,Allocator>                     Base;
		typedef typename Base::node_alloc_type                             node_alloc_type;
	public:
		typedef T                                                          value_type;
		typedef Allocator                                                  allocator_type;
		typedef value_type&                                                reference;
		typedef const value_type&                                          const_reference;
		typedef typename std::allocator_traits<Allocator>::size_type       size_type;
		typedef typename std::allocator_traits<Allocator>::difference_type difference_type;
		typedef typename std::allocator_traits<Allocator>::pointer         pointer;
		typedef typename std::allocator_traits<Allocator>::const_pointer   const_pointer;
		typedef detail::forward_list_iterator<T>                           iterator;
		typedef detail::forward_list_const_iterator<T>                     const_iterator;

// Member functions
/**
(constructor)
	constructs the forward_list
*/
	forward_list() :
		forward_list( Allocator() )
	{
	}

	explicit forward_list( const Allocator& alloc ) :
		_impl( node_alloc_type(alloc) )
	{
	}

/**
(destructor)
	destructs the forward_list
*/
/**
operator=
	assigns values to the container
*/
/**
assign
	assigns values to the container
*/
/**
get_allocator
	returns the associated allocator
*/
/*
Element access
*/
/**
front
	access the first element
*/
/**
Iterators
*/
/**
before_begin cbefore_begin
	returns an iterator to the element before beginning
*/
	iterator before_begin()
	{
		return iterator( &_impl._head );
	}

	const_iterator before_begin() const
	{
		return const_iterator( &_impl._head );
	}

	const_iterator cbefore_begin() const
	{
		return const_iterator( &_impl._head );
	}
/**
begin cbegin
	returns an iterator to the beginning
*/
	iterator begin()
	{
		return iterator( _impl._head._next );
	}

	const_iterator begin() const
	{
		return const_iterator( _impl._head._next );
	}

	const_iterator cbegin() const
	{
		return const_iterator( _impl._head._next );
	}
/**
end cend
	returns an iterator to the end
*/
	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator end() const
	{
		return const_iterator(nullptr);
	}

	const_iterator cend() const
	{
		return const_iterator(nullptr);
	}
/*
Capacity
*/
/**
empty
	checks whether the container is empty
*/
	bool empty() const
	{
		return _impl._head._next == nullptr;
	}
/**
max_size
	returns the maximum possible number of elements
*/
/**
Modifiers
*/
/**
clear
	clears the contents
*/
	void clear()
	{
		erase_after( &_impl._head, nullptr );
	}
/**
insert_after
	inserts elements after an element
*/
	iterator insert_after( const_iterator pos, const T& value )
	{
		return iterator( _impl.insert_after( pos, value ) );
	}

	iterator insert_after( const_iterator pos, T&& value )
	{
		return iterator( _impl.insert_after( pos, std::move(value) ) );
	}

	iterator insert_after( const_iterator pos, size_type count, const T& value );

	template< class InputIt >
	iterator insert_after( const_iterator pos, InputIt first, InputIt last );

	iterator insert_after( const_iterator pos, std::initializer_list<T> ilist )
	{
		return insert_after( pos, ilist.begin(), ilist.end() );
	}

/**
emplace_after
	constructs elements in-place after an element
*/
/**
erase_after
	erases an element after an element
*/
/**
push_front
	inserts an element to the beginning
*/
	void push_front( const T& value )
	{
		_impl.insert_after( before_begin(), value );
	}

	void push_front( T&& value )
	{
		_impl.insert_after( before_begin(), std::move(value) );
	}

/**
emplace_front
	constructs an element in-place at the beginning
*/
/**
pop_front
	removes the first element
*/
/**
resize
	changes the number of elements stored
*/
/**
swap
	swaps the contents
*/
/*
Operations
*/
/**
merge
	merges two sorted lists
*/
/**
splice_after
	moves elements from another forward_list
*/
/**
remove remove_if
	removes elements satisfying specific criteria
*/
/**
reverse
	reverses the order of the elements
*/
/**
unique
	removes consecutive duplicate elements
*/
/**
sort
	sorts the elements
*/

	private:
		detail::forward_list_base<T,Allocator> _impl;
};

} // namespace ads

#endif // FORWARD_LIST_H

