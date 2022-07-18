#ifndef SBROWSER2_BLOB_HPP
#define SBROWSER2_BLOB_HPP

#include "dom_object.hpp"
namespace file_api {class blob;}

#include "ext/map.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include <future>
#include <v8-array-buffer.h>
#include <v8pp/convert.hpp>
namespace streams::readable {class readable_stream;}


class file_api::blob
        : public virtual dom_object
{
public aliases:
    using blob_part_t = ext::variant<blob, ext::string_view, v8::ArrayBufferView>;

public constructors:
    blob(ext::vector_view<blob_part_t> blob_parts, ext::string_any_map_view options = {});

public js_methods:
    auto slice(ext::optional<ext::number<longlong>> start, ext::optional<ext::number<longlong>> end, ext::optional<ext::string> content_type) -> blob;
    auto stream() -> streams::readable::readable_stream;
    auto text() -> std::promise<ext::string>;
    auto array_buffer() -> std::promise<v8::Local<v8::ArrayBuffer>>;

public js_properties:
    ext::property<ext::number<ulonglong>> size;
    ext::property<ext::string> type;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    ext::string m_snapshot_state;
};

#endif //SBROWSER2_BLOB_HPP
