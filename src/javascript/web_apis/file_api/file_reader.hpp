#ifndef SBROWSER2_FILE_READER_HPP
#define SBROWSER2_FILE_READER_HPP


#include "dom/nodes/event_target.hpp"
namespace file_api {class file_reader;}

namespace dom::other {class dom_exception;}
namespace file_api {class blob;}


class file_api::file_reader
        : public dom::nodes::event_target
{
public constructors:
    file_reader();

public js_static_constants:
    constexpr static const ext::number<ushort> EMPTY = 0;
    constexpr static const ext::number<ushort> LOADING = 1;
    constexpr static const ext::number<ushort> DONE = 2;

public js_methods:
    auto read_as_array_buffer(blob& blob_object) -> void;
    auto read_as_binary_string(blob& blob_object) -> void;
    auto read_as_text(blob& blob_object, ext::string_view encoding) -> void;
    auto read_as_data_url(blob& blob_object) -> void;

    auto abort() -> void;

public js_properties:
    ext::property<ext::number<ushort>> ready_state;
    ext::property<ext::string> result;
    ext::property<dom::other::dom_exception*> error;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_FILE_READER_HPP
