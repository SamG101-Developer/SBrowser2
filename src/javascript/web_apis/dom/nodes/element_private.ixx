module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.element_private;
import apis.dom.node_private;
import apis.dom.mixins.child_node_private;
import apis.dom.mixins.document_or_element_node_private;
import apis.dom.mixins.non_document_type_child_node_private;
import apis.dom.mixins.parentable_node_private;
import apis.dom.mixins.slottable_private;
import apis.aria.mixins.aria_mixin_private;

import ext.boolean;
import ext.queue;
import ext.string;
import ext.vector;


DEFINE_PRIVATE_CLASS(dom, element)
        : dom::node_private
        , mixins::child_node_private
        , mixins::document_or_element_node_private
        , mixins::non_document_type_child_node_private
        , mixins::parentable_node_private
        , mixins::slottable_private
        , aria::mixins::aria_mixin_private
//        , css::css_web_animations::mixins::animatable_private
{
    MAKE_QIMPL(element);

    ext::string namespace_;
    ext::string namespace_prefix;
    ext::string local_name;
    detail::custom_element_definition_t* custom_element_definition;
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
