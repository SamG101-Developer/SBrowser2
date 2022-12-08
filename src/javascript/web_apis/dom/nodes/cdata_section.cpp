module apis.dom.cdata_section_private;


dom::nodes::character_data::character_data()
{
    INIT_PIMPL;
}


auto dom::nodes::cdata_section::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the fixed string "#cdata-section". Apply custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        return u"#cdata-section";
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::cdata_section::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<text>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
