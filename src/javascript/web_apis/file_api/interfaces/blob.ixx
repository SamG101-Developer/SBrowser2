module;
#include "ext/macros.hpp"


export module apis.file_api.blob;
import apis.dom_object;

IMPORT_ALL_TYPES(file_api);
IMPORT_ALL_TYPES(streams);


DEFINE_PUBLIC_CLASS(file_api, blob)
        : public virtual dom_object
{
public constructors:
    blob(ext::vector<detail::blob_part_t>&& blob_parts = {}, detail::blob_property_bag_t&& options = {});
    MAKE_PIMPL(blob);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_SERIALIZABLE;

private js_methods:
    auto slice(ext::number<longlong> start = 0, ext::number<longlong> end = ext::number<longlong>::max(), ext::string_view content_type = u"") -> std::unique_ptr<blob>;
    auto stream() -> std::unique_ptr<streams::readable_stream>;
    auto text() -> ext::promise<ext::string>;
    auto array_buffer() -> ext::promise<ext::array_buffer>;

private js_properties:
    DEFINE_GETTER(size, ext::number<ulonglong>);
    DEFINE_GETTER(type, ext::string);
};
