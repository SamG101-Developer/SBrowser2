#ifndef SBROWSER2_FILE_READER_HPP
#define SBROWSER2_FILE_READER_HPP

#include "dom/nodes/event_target.hpp"
namespace file_api {class file_reader;}
namespace file_api {class file_reader_private;}

#include INCLUDE_INNER_TYPES(file_api)
namespace dom::other {class dom_exception;}
namespace file_api {class blob;}


class file_api::file_reader
        : public dom::nodes::event_target
{
public constructors:
    file_reader();
    MAKE_PIMPL(file_reader);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

public js_static_constants:
    constexpr static const ext::number<ushort> EMPTY = 0;
    constexpr static const ext::number<ushort> LOADING = 1;
    constexpr static const ext::number<ushort> DONE = 2;

public js_methods:
    auto read_as_array_buffer(blob* blob_object) -> void;
    auto read_as_text(blob* blob_object, ext::string_view encoding = u"") -> void;
    auto read_as_data_url(blob* blob_object) -> void;
    auto abort() -> void;

private js_properties:
    DEFINE_GETTER(ready_state, ext::number<ushort>);
    DEFINE_GETTER(result, detail::result_t);
    DEFINE_GETTER(error, dom::other::dom_exception*);
};


#endif //SBROWSER2_FILE_READER_HPP
