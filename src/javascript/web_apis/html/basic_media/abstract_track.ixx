module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.html.abstract_track;
import apis._.dom_object;
import apis.html.types;

import ext.tuple;
import ext.string;

import js.env.module_type;

namespace media::source {class source_buffer;}


DEFINE_PUBLIC_CLASS(html, abstract_track)
        : public virtual dom_object
{
public constructors:
    abstract_track();
    MAKE_PIMPL(abstract_track);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(label, ext::string_view);
    DEFINE_GETTER(language, ext::string_view);
    DEFINE_GETTER(kind, detail::text_track_kind_t);

    /* [MEDIA-SOURCE] */
    DEFINE_GETTER(source_buffer, media::source::source_buffer*);
};
