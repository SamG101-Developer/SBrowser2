#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_PARSING_DOM_PARSER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_PARSING_DOM_PARSER_HPP


namespace dom_parsing {class dom_parser;}

#include INCLUDE_INNER_TYPES(dom_parsing)
namespace dom::nodes {class document;}


class dom_parsing::dom_parser
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(dom_parser);
    dom_parser() = default;

public js_methods:
    auto parse_from_string(ext::string&& string, detail::supported_type_t type) -> dom::nodes::document;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_PARSING_DOM_PARSER_HPP
