module;
#include "ext/macros/pimpl.hpp"
#include <tl/optional.hpp>


export module apis.dom.element_private;
import apis.dom.node_private;
import apis.dom.mixins.child_node_private;
import apis.dom.mixins.document_or_element_node_private;
import apis.dom.mixins.non_document_type_child_node_private;
import apis.dom.mixins.parentable_node_private;
import apis.dom.mixins.slottable_private;
import apis.aria.mixins.aria_mixin_private;

import ext.boolean;
import ext.memory;
import ext.optional;
import ext.queue;
import ext.string;
import ext.vector;

namespace dom {class attr;}
namespace dom {class shadow_root;}


DEFINE_PRIVATE_CLASS(dom, element)
        : dom::node_private
        , dom::child_node_private
        , dom::document_or_element_node_private
        , dom::non_document_type_child_node_private
        , dom::parentable_node_private
        , dom::slottable_private
        , aria::mixins::aria_mixin_private
        // , css::css_web_animations::mixins::animatable_private
{
    MAKE_QIMPL(element);

    auto locate_a_namespace_prefix(ext::string_view namespace_) const -> ext::string;
    auto locate_a_namespace(ext::string_view prefix) const -> ext::string;

    auto is_html() const -> ext::boolean;
    auto qualified_name() const -> ext::string;
    auto html_uppercase_qualified_name() const -> ext::string;
    auto html_lowercase_qualified_name() const -> ext::string;

    auto set_attribute(std::unique_ptr<attr>&& attribute) -> attr*;
    auto remove_attribute(attr* attribute) -> attr*;
    auto toggle_attribute(attr* attribute, ext::optional<ext::boolean> force, ext::string_view qualified_name = u"", ext::string_view namespace_ = u"") -> attr*;

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
