#ifndef SBROWSER2_BLOB_HPP
#define SBROWSER2_BLOB_HPP

#include "dom_object.hpp"
namespace file_api {class blob;}
namespace file_api {class blob_private;}

#include "ext/map.hpp"
#include "ext/optional.hpp"
#include "ext/variant.hpp"
#include "ext/vector.hpp"
#include "ext/promise.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(file_api)
namespace streams::readable {class readable_stream;}


class file_api::blob
        : public virtual dom_object
{
public constructors:
    blob(ext::vector<detail::blob_part_t>&& blob_parts = {}, detail::blob_property_bag_t&& options = {});
    MAKE_PIMPL(blob);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_SERIALIZABLE;

public js_methods:
    auto slice(ext::number<longlong> start = 0, ext::number<longlong> end = ext::number<longlong>::max(), ext::string_view content_type = u"") -> std::unique_ptr<blob>;
    auto stream() -> std::unique_ptr<streams::readable::readable_stream>;
    auto text() -> ext::promise<ext::string>;
    auto array_buffer() -> ext::promise<ext::array_buffer>;

private js_properties:
    DEFINE_GETTER(size, ext::number<ulonglong>);
    DEFINE_GETTER(type, ext::string);
};


#endif //SBROWSER2_BLOB_HPP
