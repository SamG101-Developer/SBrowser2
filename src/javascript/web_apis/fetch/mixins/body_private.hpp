#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_MIXINS_BODY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_MIXINS_BODY_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include "ext/functional.hpp"
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(fetch::mixins, body)
        : virtual dom_object_private
{
    MAKE_QIMPL(body);

    ext::function<auto() -> ext::string> mime_type_algorithm;
    std::unique_ptr<detail::body_t> body;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FETCH_MIXINS_BODY_PRIVATE_HPP
