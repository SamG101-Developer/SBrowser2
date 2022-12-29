#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SERIALIZATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SERIALIZATION_INTERNALS_HPP

#include "ext/keywords.ixx"
#include INCLUDE_CONCEPTS(html)

namespace html::detail
{
    template <html::concepts::is_serializable T>
    auto structured_clone(T* value)
            -> std::unique_ptr<T>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_SERIALIZATION_INTERNALS_HPP
