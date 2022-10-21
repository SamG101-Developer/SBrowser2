#include "html_dialog_element.hpp"
#include "dom/_typedefs.hpp"
#include "html_dialog_element_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/shadow_internals.hpp"

#include "html/detail/focus_internals.hpp"


html::elements::html_dialog_element::html_dialog_element()
{
    INIT_PIMPL(html_dialog_element);
    ACCESS_PIMPL(html_dialog_element);

    d->remove_steps =
            [](dom::nodes::node* parent)
            {
        // TODO : layers
            };

    HTML_CONSTRUCTOR;
}


auto html::elements::html_dialog_element::show() -> void
{
    ACCESS_PIMPL(html_dialog_element);
    return_if (d->open);
    d->open = false;
    d->previously_focused_element = detail::focused_element();
    detail::dialog_focusing_steps();
}


auto html::elements::html_dialog_element::show_modal() -> void
{
    ACCESS_PIMPL(html_dialog_element);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [d] {return d->open;},
            u8"HTMLDialogElement is already open");


    dom::detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [this] {return !dom::detail::connected(this);},
            u8"HTMLDialogElement must be connected");

    d->open = false;
    d->is_modal_flag = true;

    detail::block_document_by_modal_dialog(d->node_document, this);
    // TODO : layers

    d->previously_focused_element = detail::focused_element();
    detail::dialog_focusing_steps();
}


auto html::elements::html_dialog_element::close(ext::string&& return_value) -> void
{
    detail::close_dialog(this, std::move(return_value));
}


auto html::elements::html_dialog_element::get_open() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_dialog_element);
        return d->open;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_dialog_element::get_return_value() const -> ext::string_view
{
    ACCESS_PIMPL(const html_dialog_element);
    return d->return_value;
}


auto html::elements::html_dialog_element::set_open(ext::boolean new_open) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_dialog_element);
        return d->open = new_open;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_dialog_element::set_return_value(ext::string new_return_value) -> ext::string
{
    ACCESS_PIMPL(html_dialog_element);
    return d->return_value = std::move(new_return_value);
}


auto html::elements::html_dialog_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_dialog_element>{isolate}
        .inherit<html_element>()
        .ctor<>()
        .property("open", &html_dialog_element::get_open, &html_dialog_element::set_open)
        .property("returnValue", &html_dialog_element::get_return_value, &html_dialog_element::set_return_value)
        .auto_wrap_objects();
}
