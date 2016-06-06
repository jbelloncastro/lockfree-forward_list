
#ifdef FORWARD_LIST_NODE_H
#define FORWARD_LIST_NODE_H

namespace ads {
namespace detail {

/**
 * @brief A helper basic node class for %forward_list.
 */
template<
	class T,
	class Allocator
> class forward_list_base<T,Allocator>::node {
	public:
// Member types
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef Allocator value_allocator_type;

// Member functions
		node() = delete;

		node( const node& ) = delete;

		node( Allocator allocator = Allocator(), const_reference value ) :
			_next( nullptr ),
			_value( value )
		{
		}

		template < typename... Args >
		node( Allocator allocator = Allocator(), Args&&... args ) :
			_next( nullptr ),
			_value( std::forward<Args>(args)... )
		{
		}

		virtual ~node()
		{
		}

	private:
		node*     _next;
		T         _value;
};

} // namespace detail
} // namespace ads

#endif // FORWARD_LIST_NODE_H

