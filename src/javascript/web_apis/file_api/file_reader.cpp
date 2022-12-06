#include "file_reader.hpp"
#include "file_reader_private.hpp"

#include INCLUDE_INNER_TYPES(file_api)


#include "html/detail/task_internals.hpp"
#include "file_api/detail/file_internals.hpp"

#include <magic_enum.hpp>


file_api::file_reader::file_reader()
{
    INIT_PIMPL(file_reader);
}


auto file_api::file_reader::read_as_array_buffer(blob* blob_object) -> void
{
    detail::read_operation(this, blob_object); // TODO
}


auto file_api::file_reader::read_as_text(file_api::blob* blob_object, ext::string_view encoding) -> void
{
    detail::read_operation(this, blob_object, encoding); // TODO
}


auto file_api::file_reader::read_as_data_url(file_api::blob* blob_object) -> void
{
    detail::read_operation(this, blob_object); // TODO
}


auto file_api::file_reader::abort() -> void
{
    ACCESS_PIMPL(file_reader);

    if (d->state == detail::state_t::EMPTY || d->state == detail::state_t::DONE)
        return static_cast<void>(d->result = u"");

    if (d->state == detail::state_t::LOADING)
        ext::tie(d->state, d->result) = ext::make_tuple(detail::state_t::DONE, u"");

    html::detail::file_reading_task_source.queue.clear();
    // TODO : algorithm termination

    detail::fire_progress_event(u"abort", this);
    if (d->state == detail::state_t::LOADING)
        detail::fire_progress_event(u"loadend", this);
}


auto file_api::file_reader::get_ready_state() const -> ext::number<ushort>
{
    ACCESS_PIMPL(const file_reader);
    return *magic_enum::enum_index(d->state);
}


auto file_api::file_reader::get_result() const -> detail::result_t
{
    ACCESS_PIMPL(const file_reader);
    return ext::visit([]<typename T>(T&& val) mutable -> detail::result_t {return std::forward<T>(val);}, d->result); // TODO : ?
}


auto file_api::file_reader::get_error() const -> dom::other::dom_exception*
{
    ACCESS_PIMPL(const file_reader);
    return d->error.get();
}


auto file_api::file_reader::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::nodes::event_target>()
        .ctor<>()
        .function("readAsArrayBuffer", &file_reader::read_as_array_buffer)
        .function("readAsBinaryString", &file_reader::read_as_array_buffer)
        .function("readAsText", &file_reader::read_as_text)
        .function("readAsDataURL", &file_reader::read_as_data_url)
        .function("abort", &file_reader::abort)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
