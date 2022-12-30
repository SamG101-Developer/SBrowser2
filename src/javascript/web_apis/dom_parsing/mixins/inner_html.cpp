module;
#include "ext/macros/custom_operator.hpp"


module apis.dom_parsing.mixins.inner_html;

import apis.dom.node;
import apis.dom.element;
import apis.dom.shadow_root;

import ext.core;
import js.env.module_type;


auto dom_parsing::mixins::inner_html::get_inner_html() -> ext::string
{
    _CE_REACTIONS_METHOD_DEF
        decltype(auto) base = dom_cross_cast<dom::node*>(this);
        return detail::fragment_serialize(base);
    _CE_REACTIONS_METHOD_EXE
}


auto dom_parsing::mixins::inner_html::set_inner_html(ext::string&& new_inner_html) -> ext::view_of_t<ext::string&&>
{
    _CE_REACTIONS_METHOD_DEF
        decltype(auto) base = dom_cross_cast<dom::node*>(this);
        decltype(auto) context_object = dom_cast<dom::element*>(base) ?: dom_cast<dom::shadow_root*>(base)->d_func()->host.get();
        auto fragment = detail::fragment_parsing_algorithm(std::move(new_inner_html), context_object);

        if (decltype(auto) t = dom_cast<html::html_template_element*>(context_object))
            context_object = t->d_func()->template_contents();

        context_object->d_func()->replace_all(std::move(fragment), context_object);
    _CE_REACTIONS_METHOD_EXE
}
