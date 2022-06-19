#pragma once
#ifndef SBROWSER2_SET_HPP
#define SBROWSER2_SET_HPP

#include <set>

namespace     {template <typename _Vt> using container_internal = std::set<_Vt>;}
namespace ext {template <typename _Tx> class set;}

#include <ext/keywords.hpp>


template <typename _Tx>
class ext::set
        : public container_internal<_Tx>
{
public aliases:
    using outer_val_t = _Tx;

public constructors:
    using container_internal<_Tx>::container_internal;
};


#endif //SBROWSER2_SET_HPP
