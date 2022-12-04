#include "html_script_element.hpp"
#include "html_script_element_private.hpp"



#include "dom/_typedefs.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"


html::elements::html_script_element::html_script_element()
{
    INIT_PIMPL(html_script_element);
    ACCESS_PIMPL(html_script_element);

    d->cloning_steps =
            [d](dom::nodes::node* clone, dom::nodes::document* document_to_clone_into, ext::boolean deep)
            {dom_cast<html_script_element*>(clone)->d_func()->already_started = d->already_started;};

    HTML_CONSTRUCTOR;
}


auto html::elements::html_script_element::supports(ext::string_view type) -> ext::boolean
{
    auto types = {u"classic", u"module", u"importmap"};
    return ranges::contains(types, type);
}\


auto html::elements::html_script_element::get_src() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->src;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_type() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->type;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_no_module() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->no_module;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_async() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->force_async || d->async;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_defer() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->defer;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_cross_origin() const -> html::detail::cross_origin_settings_attribute_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->cross_origin;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_text() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return dom::detail::child_text_content(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_integrity() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->integrity;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_referrer_policy() const -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->referrer_policy;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::get_blocking() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_script_element);
        return d->blocking;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_src(ext::string new_src) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return d->src = std::move(new_src);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_type(ext::string new_type) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return d->type = std::move(new_type);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_no_module(ext::boolean new_no_module) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return d->no_module = new_no_module;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_async(ext::boolean new_async) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        d->force_async = false;
        return d->async = new_async;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_defer(ext::boolean new_defer) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return d->defer = new_defer;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_cross_origin(html::detail::cross_origin_settings_attribute_t new_cross_origin) -> html::detail::cross_origin_settings_attribute_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return d->cross_origin = new_cross_origin;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_text(ext::string new_text) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return dom::detail::string_replace_all(std::move(new_text), this);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_integrity(ext::string new_integrity) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return d->integrity = std::move(new_integrity);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_script_element::set_referrer_policy(referrer_policy::detail::referrer_policy_t new_referrer_policy) -> referrer_policy::detail::referrer_policy_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_script_element);
        return d->referrer_policy = new_referrer_policy;
    CE_REACTIONS_METHOD_EXE
}
