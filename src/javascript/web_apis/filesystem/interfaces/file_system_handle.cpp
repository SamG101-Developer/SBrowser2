module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros.hpp"


module apis.filesystem.file_system_handle;
import apis.filesystem.file_system_handle;
import apis.filesystem.types;

import apis.dom.detail;
import apis.dom.types;

import apis.html.detail;
import apis.html.types;

import ext.core;
import ext.js;

import js.env.realms;
import js.env.settings;
import js.env.module_type;


auto filesystem::file_system_handle::_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage) -> void
{
    ACCESS_PIMPL;
    auto e = js::env::env::relevant(this);

    serialized[u"$Origin"] = e.cpp.settings()->origin.get();
    serialized[u"$Entry" ] = d->entry;
}


auto filesystem::file_system_handle::_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage) -> this_t*
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;
    auto e = js::env::env::relevant(this);

    dom::detail::throw_v8_exception<DATA_CLONE_ERR>(
            [&e, &serialized] {return !html::detail::same_origin(*serialized[u"$Origin"].to<html::detail::origin_t*>(), *e.cpp.settings()->origin);},
            u8"Origin doesn't match relevant setting object's origin");

    d->entry = serialized[u"$Entry"].to<std::shared_ptr<detail::entry_t>>();
}


auto filesystem::file_system_handle::is_same_entry(
        filesystem::file_system_handle* other)
        const -> ext::promise<ext::boolean>
{
    ACCESS_PIMPL;
    auto e = js::env::env::relevant(this);
    auto promise = web_idl::detail::create_promise<ext::boolean>(e.js.realm());
    _GO [d, other, &e, &promise] {web_idl::detail::resolve_promise(promise, e.js.realm(), *d->entry == *other->d_func()->entry);};

    return promise;
}


auto filesystem::file_system_handle::get_kind() const -> detail::file_system_handle_kind_t
{
    ACCESS_PIMPL;
    return dom_cast<const detail::file_entry_t*>(d->entry.get())
            ? detail::file_system_handle_kind_t::FILE
            : detail::file_system_handle_kind_t::DIRECTORY;
}


auto filesystem::file_system_handle::get_name() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->entry->name;
}


auto filesystem::file_system_handle::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("isSameEntry", &file_system_handle::is_same_entry)
        .property("kind", &file_system_handle::get_kind)
        .property("name", &file_system_handle::get_name)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
