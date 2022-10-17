#include "content_editable.hpp"
#include "content_editable_private.hpp"

#include "html/detail/editing_internals.hpp"


auto html::mixins::content_editable::get_is_content_editable() const -> ext::boolean
{
    ACCESS_PIMPL(const content_editable);
    return detail::is_editing_host(this) || exec_command::detail::is_editable(this);
}


auto html::mixins::content_editable::get_content_editable() const -> ext::string
{
    ACCESS_PIMPL(const content_editable);

    return_if (!d->content_editable.has_value()) u8"inherited";
    return *d->content_editable ? u8"true" : u8"false";
}


auto html::mixins::content_editable::get_enter_key_hit() const -> detail::editable_enter_key_hit_t
{
    ACCESS_PIMPL(const content_editable);
    return d->enter_key_hit;
}


auto html::mixins::content_editable::get_input_mode() const -> detail::editable_input_mode_t
{
    ACCESS_PIMPL(const content_editable);
    return d->input_mode;
}


auto html::mixins::content_editable::set_content_editable(ext::string new_content_editable) -> ext::string
{
    ACCESS_PIMPL(content_editable);
    return d->content_editable = new_content_editable == u8"inherited" ? ext::nullopt : std::lexical_cast<bool>(new_content_editable);
}
