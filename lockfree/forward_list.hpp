
#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "detail/forward_list_base.hpp"

#include <memory>

namespace ads {

template<
	class T,
	class Allocator = std::allocator<T>
	>
class forward_list : public detail::forward_list_base<T,Allocator> {
	public:
// Member types
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type; // Unsigned integral type (usually std::size_t)
		typedef std::ptrdiff_t difference_type; // Signed integer type (usually std::ptrdiff_t)
		typedef value_type&;
		typedef const value_type& const_reference;
		typedef std::allocator_traits<Allocator>::pointer pointer;
		typedef std::allocator_traits<Allocator>::const_pointer const_pointer;
		typedef ForwardIterator iterator;
		typedef const ForwardIterator const_iterator;

// Member functions
/**
(constructor)
	constructs the forward_list
*/
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
/**
begin cbegin
	returns an iterator to the beginning
*/
/**
end cend
	returns an iterator to the end
*/
/*
Capacity
*/
/**
empty
	checks whether the container is empty
*/
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
/**
insert_after
	inserts elements after an element
*/
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
removeremove_if
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
// Member values
		node* _head;

};

} // namespace ads

#endif // FORWARD_LIST_H

