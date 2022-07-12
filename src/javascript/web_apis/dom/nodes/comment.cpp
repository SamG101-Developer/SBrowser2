#include "comment.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"


dom::nodes::comment::comment()
{
    JS_REALM_GET_RELEVANT(this)
    owner_document = javascript::environment::realms_2::get<document*>(this_relevant_global_object, "associated_document");
}


dom::nodes::comment::comment(
        ext::string_view new_data)
        : comment()
{
    data = new_data;
}


auto dom::nodes::comment::get_node_name()
        const -> ext::string
{
    return "#comment";
}


auto dom::nodes::comment::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<comment>{isolate}
            .ctor<>()
            .ctor<ext::string_view>()
            .inherit<character_data>()
            .auto_wrap_objects();
}
