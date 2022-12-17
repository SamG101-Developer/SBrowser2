module;
#include <tl/optional.hpp>


export module apis.contact_picker.detail;
import apis.contact_picker.types;

import ext.boolean;
import ext.span;
import ext.string;
import ext.optional;


export namespace contact_picker::detail
{
    auto launch(
            ext::boolean allow_multiple,
            ext::vector_span<ext::string> properties)
            -> ext::optional<user_contact_t>;
}
