#include "xml_document.hpp"


dom::nodes::xml_document::xml_document() : INIT_PIMPL {}


auto dom::nodes::xml_document::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<xml_document>{isolate}
        .inherit<document>()
        .auto_wrap_objects();
}