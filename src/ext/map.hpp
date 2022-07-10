#pragma once
#ifndef SBROWSER2_MAP_HPP
#define SBROWSER2_MAP_HPP

#include <map>

namespace     {template <typename _Vt1, typename _Vt2> using map_internal = std::map<_Vt1, _Vt2>;}
namespace ext {template <typename _Vt1, typename _Vt2> class map;}

#include <ext/keywords.hpp>
#include <ext/optional.hpp>

namespace ext {class any;}
namespace ext {class string;}

namespace ext {using string_any_map         = ext::map<ext::string, ext::any   >;}
namespace ext {using string_any_map_view    = const string_any_map&;}
namespace ext {using string_string_map      = ext::map<ext::string, ext::string>;}
namespace ext {using string_string_map_view = const string_string_map&;}


template <typename _Tx1, typename _Tx2>
class ext::map
        : public map_internal<_Tx1, _Tx2>
{
public aliases:
    using key_t = _Tx1;
    using value_t = _Tx2;

public constructors:
    using map_internal<_Tx1, _Tx2>::map_internal;

public cpp_methods:
    auto at(_Tx1&& _Key) -> optional<_Tx2>
    {
        if (this->contains(std::forward<_Tx1>(_Key)))
            return optional<_Tx2>{map_internal<_Tx1, _Tx2>::at(std::forward<_Tx1>(_Key))};
        return optional<_Tx2>{null};
    }

    auto at(_Tx1&& _Key) const -> optional<const _Tx2>
    {
        if (this->contains(std::forward<_Tx1>(_Key)))
            return optional<const _Tx2>{map_internal<_Tx1, _Tx2>::at(std::forward<_Tx1>(_Key))};
        return optional<_Tx2>{null};
    }
};


#endif //SBROWSER2_MAP_HPP
