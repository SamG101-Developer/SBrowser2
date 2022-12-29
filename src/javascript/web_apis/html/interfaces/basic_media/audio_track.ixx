module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.html.audio_track;
import apis.html.abstract_track;

import ext.boolean;
import ext.string;
import ext.tuple;
import ext.type_traits;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(html, audio_track) final
        : public abstract_track
{
public constructors:
    audio_track();
    MAKE_PIMPL(audio_track);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(enabled, ext::boolean);
    DEFINE_SETTER(enabled, ext::boolean);
};
