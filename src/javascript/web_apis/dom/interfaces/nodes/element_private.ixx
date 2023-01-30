module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>


export module apis.dom.element:p;
import apis.dom.node;
import apis.dom.mixins.child_node;
import apis.dom.mixins.document_or_element_node;
import apis.dom.mixins.non_document_type_child_node;
import apis.dom.mixins.parentable_node;
import apis.dom.mixins.slottable;
import apis.aria.mixins.aria_mixin;
import apis.dom_parsing.mixins.inner_html;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, element)
        : dom::node_private
        , dom::child_node_private
        , dom::document_or_element_node_private
        , dom::non_document_type_child_node_private
        , dom::parentable_node_private
        , dom::slottable_private
        , aria::aria_mixin_private
        , dom_parsing::inner_html_private
{
public:
    MAKE_QIMPL(element);

public:
    ext::string namespace_;
    ext::string namespace_prefix;
    ext::string local_name;
    std::observer_ptr<detail::custom_element_definition_t> custom_element_definition;
    detail::custom_element_state_t custom_element_state;
    ext::string is;

    std::observer_ptr<shadow_root> shadow_root;
    ext::string id;
    ext::string class_;
    ext::string slot;

    ext::vector<std::unique_ptr<attr>> attribute_list;

    ext::queue<detail::reaction_t*> custom_element_reaction_queue;
    std::unique_ptr<html::detail::browsing_context_t> nested_browsing_context;

    /* [FULLSCREEN] */
    ext::boolean fullscreen_flag;

    /* [HTML] */
    ext::boolean click_in_progress_flag;

    /* [INTERSECTION-OBSERVERS] */
    ext::vector<std::unique_ptr<intersection_observer::detail::intersection_observer_registration_t>> registration_intersection_observers;
};
