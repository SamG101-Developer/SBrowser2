#include "html_field_set_element.hpp"
#include "html_field_set_element_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "html/_concepts.hpp"


html::elements::html_field_set_element::html_field_set_element()
{
    INIT_PIMPL(html_field_set_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_field_set_element::get_disabled() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_field_set_element);
        return d->disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_field_set_element::get_name() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_field_set_element);
        return d->name;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_field_set_element::get_form() const -> html_form_element*
{
    ACCESS_PIMPL(const html_field_set_element);
    return d->form.get();
}


auto html::elements::html_field_set_element::get_elements() const -> ranges::any_helpful_view<html::elements::html_element*>
{
    return dom::detail::descendants(this) | ranges::views::filter([]<typename T>(T* element) {return html::concepts::labelable_elements<T>;});
}


auto html::elements::html_field_set_element::set_disabled(ext::boolean new_disabled) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_field_set_element);
        return d->disabled = new_disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_field_set_element::set_name(ext::string new_name) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_field_set_element);
        return d->name = std::move(new_name);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_field_set_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_field_set_element>{isolate}
        .inherit<html_element>()
        .ctor<>()
        .property("disabled", &html_field_set_element::get_disabled, &html_field_set_element::set_disabled)
        .property("form", &html_field_set_element::get_form)
        .property("name", &html_field_set_element::get_name, &html_field_set_element::set_name)
        .property("type", &html_field_set_element::get_type)
        .property("elements", &html_field_set_element::get_elements)
        .auto_wrap_objects();
}
