#include "comment.hpp"
#include "comment_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/window.hpp"


dom::nodes::comment::comment(ext::string&& new_data)
{
    INIT_PIMPL(comment);
    ACCESS_PIMPL(comment);

    JS_REALM_GET_RELEVANT(this);
    d->node_document = v8pp::from_v8<window*>(this_relevant_agent, this_relevant_global_object)->d_func()->document;
    d->data = std::move(new_data);
}


auto dom::nodes::comment::get_node_name() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        return u8"#comment";
    CE_REACTIONS_METHOD_EXE
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
