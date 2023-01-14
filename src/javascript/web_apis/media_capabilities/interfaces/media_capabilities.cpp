module;
#include "ext/macros.hpp"
#include "ext/macros/custom_operator.hpp"


module apis.media_capabilities.media_capabilities;
import apis.media_capabilities.detail;
import apis.media_capabilities.types;

import apis.dom.types;
import apis.dom.dom_exception;

import apis.web_idl.detail;

import ext.core;
import ext.js;
import js.env.module_type;
import js.env.realms;


auto media_capabilities::media_capabilities::decoding_info(
        detail::media_decoding_configuration_t&& configuration)
        -> ext::promise<detail::media_capabilities_decoding_info_t>
{
    // Get the current JavaScript environment and create a promise that will be modified asynchronously.
    using enum dom::detail::dom_exception_error_t;
    auto e = js::env::env::current();
    auto promise = ext::promise<detail::media_capabilities_decoding_info_t>{};

    // If the 'configuration' isn't valid for decoding, then reject the 'promise' with a JavaScript TypeError and return
    // the 'promise'.
    if (!detail::is_valid_media_decoding_configuration(std::move(configuration)))
        return web_idl::detail::reject_promise(promise, e.js.realm(), v8::Exception::TypeError(v8pp::to_v8(e.js.agent(), "Invalid 'configuration'")));

    // If the 'configuration' contains a "keySystemConfiguration" entry and the global object is a WorkerGlobalScope,
    // then reject the 'promise' with a INVALID_STATE_ERR DomException and return the 'promise'.
    if (configuration.contains(u"keySystemConfiguration") && e.cpp.global<html::worker_global_scope*>())
        return web_idl::detail::reject_promise(promise, e.js.realm(), dom::dom_exception{u8"Global object can not be a WorkerGlobalScope", INVALID_STATE_ERR});

    // If the 'configuration' contains a "keySystemConfiguration" entry and the JavaScript environment isn't secure,
    // then reject the 'promise' with a SECURITY_ERR DomException and return the 'promise'.
    if (configuration.contains(u"keySystemConfiguration") && secure_contexts::detail::is_environment_settings_object_in_secure_context(e))
        return web_idl::detail::reject_promise(promise, e.js.realm(), dom::dom_exception{u8"Global env settings must be in a secure context", SECURITY_ERR});;

    // Resolve the promise asynchronously, with the newly created media capabiltiies decoding information dictonary,
    // tuned by the 'configuration'.
    _GO ext::bind_front(web_idl::detail::resolve_promise, promise, e.js.realm(), detail::create_media_capabilities_decoding_info(std::move(configuration)));
    return promise;
}


auto media_capabilities::media_capabilities::encoding_info(
        detail::media_encoding_configuration_t&& configuration)
        -> ext::promise<detail::media_capabilities_encoding_info_t>
{
    // Get the current JavaScript environment and create a promise that will be modified asynchronously.
    auto e = js::env::env::current();
    auto promise = ext::promise<detail::media_capabilities_decoding_info_t>{};

    // If the 'configuration' isn't valid for encoding, then reject the 'promise' with a JavaScript TypeError and return
    // the 'promise'.
    if (!detail::is_valid_media_configuration(std::move(configuration)))
        return web_idl::detail::reject_promise(promise, e.js.realm(), v8::Exception::TypeError(v8pp::to_v8(e.js.agent(), "Invalid 'configuration'")));

    // Resolve the promise asynchronously, with the newly created media capabiltiies encoding information dictonary,
    // tuned by the 'configuration'.
    _GO ext::bind_front(web_idl::detail::resolve_promise, promise, e.js.realm(), detail::create_media_capabilities_encoding_info(std::move(configuration)));
    return promise;
}


auto media_capabilities::media_capabilities::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .function("decodingInfo", &media_capabilities::decoding_info)
        .function("encodingInfo", &media_capabilities::encoding_info)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
