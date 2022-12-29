module;
#include "ext/macros.hpp"


export module apis.dom.cdata_section;
import apis.dom.text;


DEFINE_PUBLIC_CLASS(dom, cdata_section) final
        : public dom::text
{
public constructors:
    cdata_section();
    MAKE_PIMPL(cdata_section);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return CDATA_SECTION_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
};
