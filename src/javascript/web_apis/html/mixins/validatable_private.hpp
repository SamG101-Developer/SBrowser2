#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

namespace html::other {class validity_state;}


DEFINE_PRIVATE_CLASS(html::mixins, validatable) : virtual dom_object_private
{
    std::unique_ptr<other::validity_state> validity_state;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_PRIVATE_HPP
