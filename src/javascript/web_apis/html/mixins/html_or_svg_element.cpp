#include "html_or_svg_element.hpp"
#include "dom_object.hpp"
#include "html_or_svg_element_private.hpp"

#include "dom/detail/customization_internals.hpp"

#include "html/_typedefs.hpp"
#include "html/detail/focus_internals.hpp"


html::mixins::html_or_svg_element::html_or_svg_element()
{
    INIT_PIMPL(html_or_svg_element);

    ACCESS_PIMPL(html_or_svg_element);
    d->insertion_steps = [] {/* TODO */};
}


auto html::mixins::html_or_svg_element::focus(detail::focus_options_t&& options) -> void
{
    ACCESS_PIMPL(html_or_svg_element);
    return_if (d->locked_for_focus);

    d->locked_for_focus = true;
    detail::focusing_steps(this);
    if (options[u"focusVisible"]) detail::indicate_focus();
    if (!options[u"preventScroll"]) detail::scroll_element_into_view(u"auto");
    d->locked_for_focus = false;
}


auto html::mixins::html_or_svg_element::blur()
{
    detail::unfocusing_steps(this);
}


auto html::mixins::html_or_svg_element::get_nonce() const -> ext::string_view
{
    ACCESS_PIMPL(const html_or_svg_element);
    return d->cryptographic_nonce;
}


auto html::mixins::html_or_svg_element::get_autofocus() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_or_svg_element);
        return d->autofocus;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_or_svg_element::get_tab_index() const -> ext::number<long>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_or_svg_element);
        return d->tab_index;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_or_svg_element::set_nonce(ext::string new_nonce) -> ext::string
{
    ACCESS_PIMPL(html_or_svg_element);
    return d->cryptographic_nonce = std::move(new_nonce);
}


auto html::mixins::html_or_svg_element::set_autofocus(ext::boolean new_autofocus) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_or_svg_element);
        return d->autofocus = new_autofocus;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_or_svg_element::set_tab_index(ext::number<long> new_tab_index) -> ext::number<long>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_or_svg_element);
        return d->tab_index = new_tab_index;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::html_or_svg_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_or_svg_element>{isolate}
        .inherit<dom_object>()
        .auto_wrap_objects(); // TODO

    return std::move(conversion);
}
