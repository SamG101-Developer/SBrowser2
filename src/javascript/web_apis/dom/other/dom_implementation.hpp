#ifndef SBROWSER2_DOM_IMPLEMENTATION_HPP
#define SBROWSER2_DOM_IMPLEMENTATION_HPP

#include "dom_object.hpp"
namespace dom::other {class dom_implementation;}
namespace dom::other {class dom_implementation_private;}

namespace dom::nodes {class document_type;}
namespace dom::nodes {class document;}
namespace dom::nodes {class xml_document;}


class dom::other::dom_implementation
        : public virtual dom_object
{
public constructors:
    dom_implementation();
    MAKE_PIMPL(dom_implementation);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    _EXT_NODISCARD auto create_document_type(ext::string&& qualified_name, ext::string&& public_id, ext::string&& system_id) const -> std::unique_ptr<nodes::document_type>;
    _EXT_NODISCARD auto create_document(ext::string&& namespace_, ext::string&& qualified_name, std::unique_ptr<nodes::document_type>&& document_type) const -> std::unique_ptr<nodes::xml_document>;
    _EXT_NODISCARD auto create_html_document(ext::string&& title = u"") const -> std::unique_ptr<nodes::document>;
};


#endif //SBROWSER2_DOM_IMPLEMENTATION_HPP
