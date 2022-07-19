#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include <veque.hpp>


_EXT_BEGIN

template <typename _Vt>
using vector = veque::veque<_Vt>;

template <typename _Vt>
using vector_view = const vector<_Vt>&;

_EXT_END


#endif //SBROWSER2_VECTOR_HPP
