module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.file_api.file;
import apis.file_api.blob;
import apis.file_api.types;

import ext.core
import js.env.module_type;


DEFINE_PUBLIC_CLASS(file_api, file) final
        : public blob
{
public constructors:
    file();
    file(ext::vector<detail::blob_part_t>&& file_bits, ext::string&& file_name, detail::file_property_bag_t&& options = {});
    MAKE_PIMPL(file);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_SERIALIZABLE;

private js_properties:
    DEFINE_GETTER(name, ext::string);
    DEFINE_GETTER(last_modified, ext::number<longlong>);
};
