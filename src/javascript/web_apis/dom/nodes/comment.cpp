#include "comment.hpp"
#include "comment_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"


dom::nodes::comment::comment(ext::string&& new_data)
{
    INIT_PIMPL(comment);
    auto e = js::env::env::relevant(this);

    ACCESS_PIMPL(comment);
    d->node_document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();
    d->data = std::move(new_data);
}


auto dom::nodes::comment::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the fixed string "#comment". Apply custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        return u"#comment";
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::comment::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<comment>{isolate}
        .inherit<character_data>()
        .ctor<>()
        .ctor<ext::string&&>()
        .auto_wrap_objects();

    return std::move(conversion);
}
