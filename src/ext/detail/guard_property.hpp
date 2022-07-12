#ifndef SBROWSER2_GUARD_PROPERTY_HPP
#define SBROWSER2_GUARD_PROPERTY_HPP

namespace ext::detail {template <typename _Tx> struct guard_property;}

#include "ext/detail/meta_property.hpp"


#define property_guard(p) ext::detail::guard_property _PropertyGuard{p}


template <typename _Tx>
struct ext::detail::guard_property
{
public:
    explicit guard_property(const ext::property<_Tx>& _PropertyToGuard): _Property(_PropertyToGuard) {unlock_property(_PropertyToGuard);}
    ~guard_property() {lock_property(_Property);}

private:
    ext::property<_Tx>& _Property;
};

#endif //SBROWSER2_GUARD_PROPERTY_HPP
