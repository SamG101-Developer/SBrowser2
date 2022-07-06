#include "xpath_ns_resolver.hpp"


auto dom::xpath::xpath_ns_resolver::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<xpath_ns_resolver>{isolate}
            .inherit<dom_object>()
            .function("lookupNamespaceURI", &xpath_ns_resolver::lookup_namespace_uri)
            .auto_wrap_objects();
}
