module;
#include "ext/macros.hpp"


export module apis.file_api.file_reader;
import apis.dom.event_target;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(file_api);


DEFINE_PUBLIC_CLASS(file_api, file_reader) final
        : public dom::event_target
{
public constructors:
    file_reader();
    MAKE_PIMPL(file_reader);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

private js_static_constants:
    constexpr static const ext::number<ushort> EMPTY = 0;
    constexpr static const ext::number<ushort> LOADING = 1;
    constexpr static const ext::number<ushort> DONE = 2;

private js_methods:
    auto read_as_array_buffer(blob* blob_object) -> void;
    auto read_as_text(blob* blob_object, ext::string_view encoding = u"") -> void;
    auto read_as_data_url(blob* blob_object) -> void;
    auto abort() -> void;

private js_properties:
    DEFINE_GETTER(ready_state, ext::number<ushort>);
    DEFINE_GETTER(result, detail::result_t);
    DEFINE_GETTER(error, dom::dom_exception*);
};
