module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.cdata_section;
import apis.dom.text;
import ext.number;
import ext.string;
import ext.tuple;
import ext.type_traits;
import js.env.module_type;


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
