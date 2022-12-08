#include "html_label_element.hpp"
#include "html_label_element_private.hpp"




auto html::elements::html_label_element::get_form() const -> html_form_element*
{
    ACCESS_PIMPL(const html_label_element);
    return_if (!d->labeled_control.get()) nullptr;
    return_if (!detail::is_form_associated(d->labeled_control.get())) nullptr;
    return detail::form_owner(d->labeled_control.get()); // TODO : casting, then d-func()->form-owner.get()
}


auto html::elements::html_label_element::get_control() const -> html_element*
{
    ACCESS_PIMPL(const html_label_element);
    return d->labeled_control.get();
}


auto html::elements::html_label_element::get_html_for() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_label_element);
        return d->for_;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_label_element::set_html_for(ext::string new_html_for) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_label_element);
        return d->for_ = std::move(new_html_for);
    CE_REACTIONS_METHOD_EXE
}
