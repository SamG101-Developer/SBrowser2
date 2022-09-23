#include "comment.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"


dom::nodes::comment::comment(ext::string&& new_data)
{
    JS_REALM_GET_RELEVANT(this);
    node::d_ptr->node_document = v8pp::from_v8<window*>(this_relevant_agent, this_relevant_global_object)->document();
    character_data::d_ptr->data = std::move(new_data);
}


auto dom::nodes::comment::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<comment>{isolate}
        .inherit<character_data>()
        .ctor<>()
        .ctor<ext::string&&>()
        .auto_wrap_objects();

    return std::move(conversion);
}
