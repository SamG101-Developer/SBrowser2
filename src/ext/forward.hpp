#ifndef SBROWSER2_SRC_EXT_FORWARD_HPP
#define SBROWSER2_SRC_EXT_FORWARD_HPP

#include "ext/concepts.hpp"
#include "ext/keywords.hpp"


_EXT_BEGIN

class boolean;
class datetime;
class string;
class string_view;
template <typename ...Ts> class function;
template <typename ...Ts> class function_view;
template <typename K, typename V> class map;
template <typename K, typename V> class map_view;
template <typename K, typename V> class map_like;
template <typename K, typename V> class map_like_linked;
template <arithmetic T> class number;
template <typename T> class optional;
template <typename K, typename V> class pair;
template <typename K, typename V> class pair_view;
template <typename K, typename V> class promise;
template <typename T> class property;
template <typename T> class queue;
template <typename T> class stack;
class thread_pool;
template <typename ...Ts> class tuple;
template <typename ...Ts> class variant;
template <typename T> class vector;
template <typename T> class vector_view;

_EXT_END


#endif //SBROWSER2_SRC_EXT_FORWARD_HPP
