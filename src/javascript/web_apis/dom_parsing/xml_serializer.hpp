#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_PARSING_DETAIL_XML_SERIALIZER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_PARSING_DETAIL_XML_SERIALIZER_HPP


namespace dom_parsing {class xml_serializer;}

namespace dom::nodes {class node;}


class dom_parsing::xml_serializer
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(xml_serializer);
    xml_serializer() = default;

public js_methods:
    auto serialize_to_string(dom::nodes::node* root) -> ext::string;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_PARSING_DETAIL_XML_SERIALIZER_HPP
