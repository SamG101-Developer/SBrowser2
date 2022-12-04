#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE__TYPEDEFS_HPP





#include "ext/vector.hpp"
#include "ext/span.hpp"
namespace performance_timeline {class performance_entry;}
namespace performance_timeline {class performance_observer;}


namespace performance_timeline::detail
{
    struct performance_entry_buffer_map_tuple_t;

    enum class performance_observer_type_t {UNDEFINED, MULTIPLE, SINGLE};

    using performance_observer_callback_options_t = ext::map<ext::string, ext::any>;
    using performance_observer_init_t = ext::map<ext::string, ext::any>;
    using performance_entry_list_t = ext::vector<performance_entry*>;
    using performance_entry_buffer_map_t = ext::map<ext::string, performance_entry_buffer_map_tuple_t>;
    using performance_observer_callback_t = ext::function<void(
            ext::vector_span<performance_observer*>,
            performance_observer*,
            performance_observer_callback_options_t)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE__TYPEDEFS_HPP
