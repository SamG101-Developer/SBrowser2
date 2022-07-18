#ifndef SBROWSER2_DOM_IMPLEMENTATION_HPP
#define SBROWSER2_DOM_IMPLEMENTATION_HPP

#include "dom_object.hpp"
namespace dom::other {class dom_implementation;}

namespace dom::nodes {class document_type;}
namespace dom::nodes {class document;}
namespace dom::nodes {class xml_document;}


class dom::other::dom_implementation
        : public virtual dom_object
{
public js_methods:
    [[nodiscard]] auto create_document_type(ext::string&& qualified_name, ext::string&& public_id, ext::string&& system_id) const -> nodes::document_type;
    [[nodiscard]] auto create_document(ext::string&& namespace_, ext::string&& qualified_name, nodes::document_type* document_type = nullptr) const -> nodes::xml_document;
    [[nodiscard]] auto create_html_document(ext::string&& title = "") const -> nodes::document*;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    nodes::document* m_associated_document;
};


#endif //SBROWSER2_DOM_IMPLEMENTATION_HPP
