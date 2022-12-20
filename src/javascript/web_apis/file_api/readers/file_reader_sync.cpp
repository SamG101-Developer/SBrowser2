module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.file_api.file_reader_sync;
import apis.file_api.file_reader_sync_private;
import apis.file_api.blob;

import ext.string;
import ext.tuple;

import js.env.module_type;


file_api::file_reader_sync::file_reader_sync()
{
    INIT_PIMPL;
}


auto file_api::file_reader_sync::read_as_text(
        file_api::blob* blob_object,
        ext::string_view encoding)
        -> ext::string
{
    auto stream = detail::get_stream(blob_object);
    auto reader = streams::detail::get_reader(stream.get());
    auto promise = streams::detail::read_all_bytes(reader.get());

    using namespace ext::literals;
    auto e = js::env::env::relevant(this); // TODO : env
    web_idl::detail::wait_for_promise_to_fulfill_or_reject(promise, e.js.realm());
    if (auto fulfill_info = web_idl::detail::has_fulfilled(promise, e.js.realm()); fulfill_info[0_tag])
        return detail::package_data(*fulfill_info[1_tag], u"Text", blob_object->d_func()->type, encoding);

    auto rejection_info = web_idl::detail::has_rejected<dom::other::dom_exception>(promise, e.js.realm());
    dom::detail::throw_v8_exception(std::move(*rejection_info[1_tag]));
}


auto file_api::file_reader_sync::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .ctor<>()
        .function("readAsArrayBuffer", &file_reader_sync::read_as_array_buffer)
        .function("readAsBinaryString", &file_reader_sync::read_as_array_buffer)
        .function("readAsText", &file_reader_sync::read_as_text)
        .function("readAsDataURL", &file_reader_sync::read_as_data_url)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
