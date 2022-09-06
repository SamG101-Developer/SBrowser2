#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

namespace intersection_observer {class intersection_observer;}
namespace intersection_observer {class intersection_observer_entry;}


namespace intersection_observer::detail
{
    struct intersection_observer_registration_t;

    using intersection_observer_callback_t = ext::function<void(ext::vector<intersection_observer_entry*>, intersection_observer*)>;
    using intersection_observer_init_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER__TYPEDEFS_HPP
