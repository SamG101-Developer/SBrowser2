#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include <tsl/robin_map.h>
#include <robin_hood.h>

namespace     {template <typename _Vt1, typename _Vt2> using container_internal = tsl::robin_map<_Vt1, _Vt2, robin_hood::hash<_Vt1>>;}
namespace ext {template <typename _Vt1, typename _Vt2> class map;}

#include <ext/keywords.hpp>


template <typename _Tx1, typename _Tx2>
class ext::map
        : inherits public container_internal<_Tx1, _Tx2>
{
public aliases:
    using key_t = _Tx1;
    using value_t = _Tx2;

public constructors:
    map() = default;
    map(const map&) = default;
    map(map&&) noexcept = default;
    auto operator=(const map&) -> map& = default;
    auto operator=(map&&) noexcept -> map& = default;
    ~map() {this->clear();}
};


#endif //SBROWSER2_MAP_HPP
