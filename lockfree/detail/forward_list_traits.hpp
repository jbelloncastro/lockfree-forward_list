
#ifndef FORWARD_LIST_TRAITS
#define FORWARD_LIST_TRAITS

#include <iterator>
#include <type_traits>

namespace ads {
namespace traits {

template< typename InputIterator >
using is_input_iterator = typename 
	std::enable_if<std::is_convertible<typename
		std::iterator_traits<InputIterator>::iterator_category,
		std::input_iterator_tag>::value>::type;

} // namespace traits
} // namespace ads

#endif
