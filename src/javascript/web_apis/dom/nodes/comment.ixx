module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.comment;
import apis.dom.character_data;
import ext.number;
import ext.string;
import ext.tuple;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, comment) final
        : public character_data
{
public constructors:
    explicit comment(ext::string&& new_data = u"");
    MAKE_PIMPL(comment);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return COMMENT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
};
