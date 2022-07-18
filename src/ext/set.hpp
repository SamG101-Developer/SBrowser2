#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include <tsl/robin_set.h>

namespace ext {template <typename _Vt> using set = tsl::robin_set<_Vt>;}
namespace ext {template <typename _Tx> using set_view = const set<_Tx>&;}

#endif //SBROWSER2_SET_HPP
