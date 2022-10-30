#include "content_editable.hpp"
#include "content_editable_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "html/detail/editing_internals.hpp"


auto html::mixins::content_editable::get_is_content_editable() const -> ext::boolean
{
    ACCESS_PIMPL(const content_editable);
    return detail::is_editing_host(this) || exec_command::detail::is_editable(this);
}


auto html::mixins::content_editable::get_content_editable() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const content_editable);
        return_if (!d->content_editable.has_value()) u8"inherited";
        return *d->content_editable ? u8"true" : u8"false";
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::content_editable::get_enter_key_hit() const -> detail::editable_enter_key_hit_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const content_editable);
        return d->enter_key_hit;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::content_editable::get_input_mode() const -> detail::editable_input_mode_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const content_editable);
        return d->input_mode;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::content_editable::set_content_editable(
        ext::string new_content_editable)
        -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(content_editable);
        return d->content_editable = new_content_editable == u8"inherited" ? ext::nullopt : std::lexical_cast<bool>(new_content_editable);
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::content_editable::set_enter_key_hit(
        detail::editable_enter_key_hit_t new_enter_key_hit)
        -> detail::editable_enter_key_hit_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(content_editable);
        return d->enter_key_hit = new_enter_key_hit;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::content_editable::set_input_mode(
        detail::editable_input_mode_t new_input_mode)
        -> detail::editable_input_mode_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(content_editable);
        return d->input_mode = new_input_mode;
    CE_REACTIONS_METHOD_EXE
}


auto html::mixins::content_editable::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<content_editable>{isolate}
        .inherit<dom_object>()
        .auto_wrap_objects(); // TODO

    return std::move(conversion);
}
