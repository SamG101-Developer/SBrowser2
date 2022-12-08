#include "comment.hpp"
#include "comment_private.hpp"








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


auto dom::nodes::comment::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<character_data>()
        .ctor<>()
        .ctor<ext::string&&>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
