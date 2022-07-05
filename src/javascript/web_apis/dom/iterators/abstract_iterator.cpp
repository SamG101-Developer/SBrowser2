#include "abstract_iterator.hpp"

#include <web_apis/dom/nodes/element.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/other/dom_implementation.hpp>
#include <web_apis/url/url.hpp>


dom::node_iterators::abstract_iterator::abstract_iterator()
        : filter(nullptr)
        , root(nullptr)
        , what_to_show(0)
{}


auto dom::node_iterators::abstract_iterator::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<abstract_iterator>{isolate}
            .inherit<web_apis::dom_object>()
            .var("filter", &abstract_iterator::filter, true)
            .var("root", &abstract_iterator::root, true)
            .var("whatToShow", &abstract_iterator::what_to_show, true)
            .auto_wrap_objects();
}
