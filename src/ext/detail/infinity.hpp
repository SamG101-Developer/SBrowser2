#pragma once
#ifndef SBROWSER2_INFINITY_HPP
#define SBROWSER2_INFINITY_HPP


#include "ext/keywords.hpp"
#include <limits>
#include <type_traits>


_EXT_DETAIL_BEGIN

template <typename _Tx>
class infinity final
{
public:
    infinity() = default;

public:
    operator _Tx() const                                  {return std::numeric_limits<_Tx>::infinity();};
    operator _Tx() const requires (std::is_signed_v<_Tx>) {return std::numeric_limits<_Tx>::infinity() * (_Positive ? 1 : -1);}

    auto operator-() const -> infinity {return *this;};
    auto operator+() const -> infinity {return *this;};
    auto operator-() const -> infinity requires (std::is_signed_v<_Tx>) {return infinity{._Positive = not _Positive};};
    auto operator+() const -> infinity requires (std::is_signed_v<_Tx>) {return infinity{._Positive =     _Positive};};

private:
    bool _Positive;
};


_EXT_DETAIL_END


#endif //SBROWSER2_INFINITY_HPP
