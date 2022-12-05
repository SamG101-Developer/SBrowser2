#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_GLOBAL_SCOPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_GLOBAL_SCOPE_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(dom)


DEFINE_PRIVATE_CLASS(html::workers, worklet_global_scope) : virtual dom_object_private
{
    dom::detail::module_map_t module_map;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_GLOBAL_SCOPE_PRIVATE_HPP
