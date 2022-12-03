#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/event_target_private.hpp"
#include "html/mixins/window_or_worker_global_scope_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)
namespace html::workers {class worker_location;}
namespace html::workers {class worker_navigator;}


DEFINE_PRIVATE_CLASS(html::workers, worker_global_scope)
        : dom::nodes::event_target_private
        , mixins::window_or_worker_global_scope_private
{
    std::unique_ptr<worker_location> location;
    std::unique_ptr<worker_navigator> worker_navigation;

    ext::set<ext::variant<dom::nodes::node*, worker_global_scope>> owner_set;
    detail::worjer_global_scope_type_t type;
    std::unique_ptr<url::detail::url_t> url;
    ext::string name;

    std::unique_ptr<detail::policy_container_t> policy_container;
    std::unique_ptr<detail::embedder_policy_t> embedder_policy;
    dom::detail::module_map_t module_map;
    ext::boolean cross_origin_isolated_capability;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_PRIVATE_HPP
