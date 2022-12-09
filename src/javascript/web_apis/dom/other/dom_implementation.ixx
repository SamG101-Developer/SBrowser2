module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/extended_attributes.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.dom_implementation;
import apis._.dom_object;

import ext.string;
import ext.tuple;
import js.env.module_type;

namespace dom {class document;}
namespace dom {class document_type;}
namespace dom {class xml_document;}


DEFINE_PUBLIC_CLASS(dom, dom_implementation) final
        : public virtual dom_object
{
public constructors:
    dom_implementation();
    MAKE_PIMPL(dom_implementation);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    _EXT_NODISCARD auto create_document_type(ext::string&& qualified_name, ext::string&& public_id, ext::string&& system_id) const -> std::unique_ptr<document_type>;
    _EXT_NODISCARD auto create_document(ext::string&& namespace_, ext::string&& qualified_name, std::unique_ptr<document_type>&& document_type) const -> std::unique_ptr<xml_document>;
    _EXT_NODISCARD auto create_html_document(ext::string&& title = u"") const -> std::unique_ptr<document>;
};
