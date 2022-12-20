module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"



export module apis.file_api.blob;
import apis._.dom_object;
import apis.file_api.types;

import ext.any;
import ext.boolean;
import ext.array_buffer;
import ext.enums;
import ext.map;
import ext.number;
import ext.promise;
import ext.string;
import ext.tuple;
import ext.vector;

import js.env.module_type;

namespace streams {class readable_stream;}


DEFINE_PUBLIC_CLASS(file_api, blob)
        : public virtual dom_object
{
public constructors:
    blob(ext::vector<detail::blob_part_t>&& blob_parts = {}, detail::blob_property_bag_t&& options = {});
    MAKE_PIMPL(blob);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_SERIALIZABLE;

public js_methods:
    auto slice(ext::number<longlong> start = 0, ext::number<longlong> end = ext::number<longlong>::max(), ext::string_view content_type = u"") -> std::unique_ptr<blob>;
    auto stream() -> std::unique_ptr<streams::readable_stream>;
    auto text() -> ext::promise<ext::string>;
    auto array_buffer() -> ext::promise<ext::array_buffer>;

private js_properties:
    DEFINE_GETTER(size, ext::number<ulonglong>);
    DEFINE_GETTER(type, ext::string);
};
