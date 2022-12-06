#include "node_internals.hpp"


#include "dom/nodes/node.hpp"
#include "dom/detail/tree_internals.hpp"


auto dom::detail::shadow_root_t::get_the_parent(
        events::event* event)
        -> nodes::event_target*
{
    decltype(auto) event_composed = event->composed();
    decltype(auto) event_root = detail::root(dynamic_cast<nodes::node*>(event->path()->front()->invocation_target));
    return !event_composed && event_root->d_ptr == this ? nullptr : host();
}
