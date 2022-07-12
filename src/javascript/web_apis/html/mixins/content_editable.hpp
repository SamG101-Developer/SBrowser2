#pragma once
#ifndef SBROWSER2_CONTENT_EDITABLE_HPP
#define SBROWSER2_CONTENT_EDITABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class content_editable;}


class html::mixins::content_editable
{
public js_properties:
    ext::property<ext::string> content_editable;
    ext::property<ext::string> enter_key_hit;
    ext::property<ext::string> input_mode;
    ext::property<ext::boolean> is_content_editable;
};


#endif //SBROWSER2_CONTENT_EDITABLE_HPP
