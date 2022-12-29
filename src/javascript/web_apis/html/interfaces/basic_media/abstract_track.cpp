module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.html.abstract_track;
import apis.html.abstract_track_private;
import apis.html.types;

import ext.string;
import ext.tuple;

import js.env.module_type;


auto html::abstract_track::get_id() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->id;
}


auto html::abstract_track::get_label() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->label;
}


auto html::abstract_track::get_language() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->language;
}


auto html::abstract_track::get_kind() const -> html::detail::text_track_kind_t
{
    ACCESS_PIMPL;
    return d->kind;
}


auto html::abstract_track::get_source_buffer() const -> media::source::source_buffer*
{
    ACCESS_PIMPL;
    return d->source_buffer.get();
}


auto html::abstract_track::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("id", &abstract_track::get_id)
        .property("kind", &abstract_track::get_kind)
        .property("label", &abstract_track::get_label)
        .property("language", &abstract_track::get_language)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
