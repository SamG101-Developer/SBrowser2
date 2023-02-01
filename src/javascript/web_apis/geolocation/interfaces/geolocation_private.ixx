module;
#include "ext/macros.hpp"


export module apis.geolocation.geolocation:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(geolocation, geolocation)
        : dom_object_private
{
public:
    MAKE_QIMPL(geolocation);

public:
    std::unique_ptr<geolocation_position> cached_position;
    ext::vector<ext::number<ulong>> watch_ids;
};
