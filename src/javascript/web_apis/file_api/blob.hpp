#ifndef SBROWSER2_BLOB_HPP
#define SBROWSER2_BLOB_HPP

#include "dom_object.hpp"
#include "html/mixins/serializable.hpp"
namespace file_api {class blob;}

#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(file_api)
namespace streams::readable {class readable_stream;}


class file_api::blob
        : public virtual dom_object
        , public html::mixins::serializable
{
public constructors:
    blob(ext::vector<detail::blob_part_t>&& blob_parts = {}, ext::map<ext::string, ext::any>&& options = {});

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

protected cpp_methods:
    auto m_serialize  (ext::map<ext::string, ext::any>& serialized, ext::boolean&& for_storage) -> ext::string;
    auto m_deserialize(ext::map<ext::string, ext::any>& serialized, ext::boolean&& for_storage) -> blob*;

private js_slots:
    ext::slot<ext::string> s_snapshot_state;
    ext::slot<ext::string> s_byte_sequence;

private cpp_properties:
    ext::string m_snapshot_state;
};

#endif //SBROWSER2_BLOB_HPP
