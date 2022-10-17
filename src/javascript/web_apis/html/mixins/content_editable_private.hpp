#pragma once
#include "html/_typedefs.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_CONTENT_EDITABLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_CONTENT_EDITABLE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include INCLUDE_INNER_TYPES(html)


DEFINE_PRIVATE_CLASS(html::mixins, content_editable) : virtual dom_object_private
{
    ext::optional<ext::boolean> content_editable;

    detail::editable_enter_key_hit_t enter_key_hit;
    detail::editable_input_mode_t input_mode;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_CONTENT_EDITABLE_PRIVATE_HPP
