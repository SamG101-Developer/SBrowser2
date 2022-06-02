#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include <tsl/robin_set.h>
#include <robin_hood.h>

namespace     {template <typename _Vt> using container_internal = tsl::robin_set<_Vt, robin_hood::hash<_Vt>>;}
namespace ext {template <typename _Tx> class set;}

#include <ext/keywords.hpp>


template <typename _Tx>
class ext::set
        : inherits public container_internal<_Tx>
{
public aliases:
    using value_type = _Tx;

public constructors:
    set() = default;
    set(const set&) = default;
    set(set&&) noexcept = default;
    auto operator=(const set&) -> set& = default;
    auto operator=(set&&) noexcept -> set& = default;
    ~set() {this->clear();}
};


#endif //SBROWSER2_SET_HPP
