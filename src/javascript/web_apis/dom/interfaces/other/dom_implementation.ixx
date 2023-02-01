module;
#include "ext/macros.hpp"


export module apis.dom.dom_implementation;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, dom_implementation) final
        : public virtual dom_object
{
public constructors:
    dom_implementation();
    MAKE_PIMPL(dom_implementation);
    MAKE_V8_AVAILABLE(WINDOW);

private js_methods:
    _EXT_NODISCARD auto create_document_type(ext::string&& qualified_name, ext::string&& public_id, ext::string&& system_id) const -> std::unique_ptr<document_type>;
    _EXT_NODISCARD auto create_document(ext::string&& namespace_, ext::string&& qualified_name, std::unique_ptr<document_type>&& document_type) const -> std::unique_ptr<xml_document>;
    _EXT_NODISCARD auto create_html_document(ext::string&& title = u"") const -> std::unique_ptr<document>;
};
