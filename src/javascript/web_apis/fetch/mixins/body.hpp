#ifndef SBROWSER2_BODY_HPP
#define SBROWSER2_BODY_HPP

#include "dom_object.hpp"
namespace fetch::mixins {class body;}

#include "ext/functional.hpp"
#include <future>
#include <v8-array-buffer.h>
namespace fetch::detail::body_internals {struct internal_body;}
namespace file_api {class blob;}
namespace streams::readable {class readable_stream;}
namespace xhr {class form_data;}


class fetch::mixins::body
        : public virtual dom_object
{
public js_methods:
    auto aray_buffer() -> std::promise<v8::Local<v8::ArrayBuffer>>;
    auto blob() -> std::promise<file_api::blob>;
    auto form_data() -> std::promise<xhr::form_data>;
    auto json() -> std::promise<ext::any>;
    auto text() -> std::promise<ext::string>;

public js_properties:
    ext::property<std::unique_ptr<streams::readable::readable_stream>> body;
    ext::property<ext::boolean> body_used;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_methods:
    ext::function<ext::string()> mime_type_algorithm;

private cpp_properties:
    std::unique_ptr<detail::body_internals::internal_body> m_body;
};


#endif //SBROWSER2_BODY_HPP
