#pragma once
#ifndef SBROWSER2_VECTOR_HPP
#define SBROWSER2_VECTOR_HPP

#include <veque.hpp>

namespace ext {template <typename _Vt> using vector = veque::veque<_Vt>;}
namespace ext {template <typename _Vt> using vector_view = const vector<_Vt>&;}


#endif //SBROWSER2_VECTOR_HPP
