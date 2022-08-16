#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER__TYPEDEFS_HPP

#include "ext/functional.hpp"
#include "ext/vector.hpp"
namespace intersection_observer {class intersection_observer;}
namespace intersection_observer {class intersection_observer_entry;}


namespace intersection_observer
{
    using intersection_observer_callback = ext::function<void(
            ext::vector<intersection_observer_entry*> entries,
            intersection_observer* observer)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_INTERSECTION_OBSERVER__TYPEDEFS_HPP
