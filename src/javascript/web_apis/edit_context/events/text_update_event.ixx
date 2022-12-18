module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.edit_context.text_update_event;
import apis.dom.event;

import ext.any;
import ext.map;
import ext.number;
import ext.string;
import ext.tuple;

import js.env.module_type;


DEFINE_PUBLIC_CLASS(edit_context, text_update_event) final
        : public dom::event
{
public typedefs:
    using text_update_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    text_update_event(ext::string&& event_type, text_update_event_init_t&& event_init = {});
    MAKE_PIMPL(text_update_event);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(update_range_start, ext::number<ulonglong>);
    DEFINE_GETTER(update_range_end, ext::number<ulonglong>);
    DEFINE_GETTER(selection_start, ext::number<ulonglong>);
    DEFINE_GETTER(selection_end, ext::number<ulonglong>);
    DEFINE_GETTER(composition_start, ext::number<ulonglong>);
    DEFINE_GETTER(composition_end, ext::number<ulonglong>);
    DEFINE_GETTER(text, ext::string_view);
};
