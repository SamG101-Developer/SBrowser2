#ifndef SBROWSER2_BODY_HPP
#define SBROWSER2_BODY_HPP

#include "dom_object.hpp"
namespace fetch::mixins {class body;}
namespace fetch::mixins {class body_private;}

#include INCLUDE_INNER_TYPES(fetch)

#include "ext/promise.hpp"
#include <v8-forward.h>
namespace file_api {class blob;}
namespace streams::readable {class readable_stream;}
namespace xhr {class form_data;}


class fetch::mixins::body
        : public virtual dom_object
{
public constructors:
    body();
    MAKE_PIMPL(body);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    auto array_buffer() -> ext::promise<v8::Local<v8::ArrayBuffer>>;
    auto blob() -> ext::promise<file_api::blob>;
    auto form_data() -> ext::promise<xhr::form_data>;
    auto json() -> ext::promise<ext::any>;
    auto text() -> ext::promise<ext::string>;

private js_properties:
    DEFINE_GETTER(body, streams::readable::readable_stream*);
    DEFINE_GETTER(body_used, ext::boolean);
};


#endif //SBROWSER2_BODY_HPP
