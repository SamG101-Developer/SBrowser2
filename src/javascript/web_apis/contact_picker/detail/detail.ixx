module;
#include "ext/macros/macros.hpp"
#include <tl/optional.hpp>


export module apis.contact_picker.detail;
import apis.contact_picker.types;

import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(contact_picker)
{
    auto launch(ext::boolean allow_multiple, ext::span<ext::string> properties) -> ext::optional<user_contact_t>;
}
