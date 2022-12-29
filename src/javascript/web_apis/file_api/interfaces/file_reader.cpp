module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"
#include <magic_enum.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.file_api.file_reader;
import apis.file_api.file_reader_private;
import apis.file_api.detail;
import apis.file_api.types;

import apis.dom.dom_exception;
import apis.dom.event_target;

import ext.core
import js.env.module_type;


file_api::file_reader::file_reader()
{
    INIT_PIMPL;
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
    ACCESS_PIMPL;

    // [1] If the state is EMPTY or DONE, them clear the 'result' (in the private class), and terminate the method --
    // this is because a FileReader that isn't doing anything or has finished can't be aborted (so don't run any other
    // steps), but clear the result.
    if (d->state == detail::state_t::EMPTY || d->state == detail::state_t::DONE)
        return static_cast<void>(d->result = u"");

    // [2] If the state is LOADING, set the state to DONE, and clear the result -- this is because the FileReader is
    // stopped (so is now DONE), and whenever a FileReader is aborted, the result gets cleared.
    if (d->state == detail::state_t::LOADING)
        ext::tie(d->state, d->result) = ext::make_tuple(detail::state_t::DONE, u"");

    // TODO : [3] html::detail::file_reading_task_source.queue.clear();
    // TODO : [4] algorithm termination

    detail::fire_progress_event(u"abort", this);
    if (d->state == detail::state_t::LOADING)
        detail::fire_progress_event(u"loadend", this);
}


auto file_api::file_reader::get_ready_state() const -> ext::number<ushort>
{
    ACCESS_PIMPL;
    return *magic_enum::enum_index(d->state);
}


auto file_api::file_reader::get_result() const -> detail::result_t
{
    ACCESS_PIMPL;
    return d->result;
}


auto file_api::file_reader::get_error() const -> dom::dom_exception*
{
    ACCESS_PIMPL;
    return d->error.get();
}


auto file_api::file_reader::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::event_target>()
        .ctor<>()
        .function("readAsArrayBuffer", &file_reader::read_as_array_buffer)
        .function("readAsBinaryString", &file_reader::read_as_array_buffer)
        .function("readAsText", &file_reader::read_as_text)
        .function("readAsDataURL", &file_reader::read_as_data_url)
        .function("abort", &file_reader::abort)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
