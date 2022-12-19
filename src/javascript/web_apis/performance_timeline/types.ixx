module;
#include <function2/function2.hpp>


export module apis.performance_timeline.types;

import ext.any;
import ext.boolean;
import ext.functional;
import ext.map;
import ext.memory;
import ext.number;
import ext.span;
import ext.string;
import ext.vector;

namespace performance_timeline {class performance_entry;}
namespace performance_timeline {class performance_observer;}


export namespace performance_timeline::detail
{
    struct performance_entry_buffer_map_tuple_t;
    struct registered_performance_observer_t;

    enum class performance_observer_type_t {UNDEFINED, MULTIPLE, SINGLE};

    using performance_observer_callback_options_t = ext::map<ext::string, ext::any>;
    using performance_observer_init_t = ext::map<ext::string, ext::any>;
    using performance_entry_buffer_map_t = ext::map<ext::string, performance_entry_buffer_map_tuple_t>;
    using performance_observer_callback_t = ext::function<void(ext::vector_span<performance_observer*>, performance_observer*, performance_observer_callback_options_t)>;
}


struct performance_timeline::detail::performance_entry_buffer_map_tuple_t
{
    ext::vector<performance_entry*> performance_entry_buffer;
    ext::number<int> max_buffer_size;
    ext::number<int> dropped_entries_count = 0;
    ext::boolean available_from_timeline;
};


struct performance_timeline::detail::registered_performance_observer_t
{
    std::observer_ptr<performance_observer> observer;
    ext::vector<performance_observer_init_t> options;
};
