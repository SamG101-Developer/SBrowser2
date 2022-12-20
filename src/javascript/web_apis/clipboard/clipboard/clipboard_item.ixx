module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"
#include <swl/variant.hpp>


export module apis.clipboard.clipboard_item;
import apis.dom_object;

import ext.any;
import ext.enums;
import ext.map;
import ext.promise;
import ext.string;
import ext.tuple;
import ext.variant;
import ext.span;

import js.env.module_type;

namespace file_api {class blob;}


DEFINE_PUBLIC_CLASS(clipboard, clipboard_item)
        : public dom_object
{
public typedefs:
    using clipboard_item_data_t = ext::promise<ext::variant<ext::string, file_api::blob*>>;
    using clipboard_item_options_t = ext::map<ext::string, ext::any>;
    enum class presentation_style_t {UNSPECIFIED, INLINE, ATTACHMENT};

public constructors:
    clipboard_item(ext::map<ext::string, clipboard_item_data_t>&& items, clipboard_item_options_t options = {});
    MAKE_PIMPL(clipboard_item);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

public js_methods:
    auto get_type(ext::string_view type) -> ext::promise<std::unique_ptr<file_api::blob>>;

public js_properties:
    DEFINE_GETTER(presentation_style, presentation_style_t);
    DEFINE_GETTER(types, ext::vector_span<ext::string>);
};
