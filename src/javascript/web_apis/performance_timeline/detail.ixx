module;
#include <memory>
#include <v8-forward.h>


export module apis.performance_timeline.detail;
import apis.performance_timeline.types;

import ext.boolean;
import ext.string;

namespace performance_timeline {class performance_entry;}


export namespace performance_timeline::detail
{
    /* [6.1] */ auto queue_performance_entry(std::shared_ptr<performance_entry> new_entry) -> void;
    /* [6.2] */ auto queue_performance_observer_task(v8::Local<v8::Object> relevant_global_object) -> void;
    /* [6.3] */ auto filter_buffer_map_by_name_and_type(ext::string_view name = u"", ext::string_view type = u"") -> void;
    /* [6.4] */ auto filter_buffer_by_name_and_type(v8::Local<v8::ArrayBuffer> buffer, ext::string_view name = u"", ext::string_view type = u"") -> void;
    /* [6.5] */ auto determine_if_performance_entry_buffer_is_full(detail::performance_entry_buffer_map_tuple_t& tuple) -> ext::boolean;
};
