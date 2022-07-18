#include "comment.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"


dom::nodes::comment::comment(ext::string&& new_data)
{
    JS_REALM_GET_RELEVANT(this)
    owner_document = javascript::environment::realms_2::get<document*>(this_relevant_global_object, "associated_document");

    data = std::move(new_data);
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
