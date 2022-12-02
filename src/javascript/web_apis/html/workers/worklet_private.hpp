#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(fetch)
#include "ext/expected.ixx"
#include "ext/map.ixx"
#include "ext/memory.ixx"
namespace fetch {class response;}
namespace html::workers {class worklet_global_scope;}


DEFINE_PRIVATE_CLASS(html::workers, worklet) : dom_object_private
{
    fetch::detail::destination_t destination;
    ext::vector<worklet_global_scope*> global_scopes;
    ext::vector<url::detail::url_t*> added_modules_list;
    ext::map<url::detail::url_t*, ext::expected<fetch::response*>> module_resposnes_map;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_PRIVATE_HPP
