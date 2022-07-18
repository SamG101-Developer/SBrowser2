#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include <tsl/robin_map.h>

namespace ext {template <typename _Vt1, typename _Vt2> using map = tsl::robin_map<_Vt1, _Vt2>;}
namespace ext {template <typename _Vt1, typename _Vt2> using map_view = const map<_Vt1, _Vt2>&;}



#endif //SBROWSER2_MAP_HPP
