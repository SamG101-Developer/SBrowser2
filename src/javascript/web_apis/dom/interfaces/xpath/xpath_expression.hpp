#pragma once
#ifndef SBROWSER2_XPATH_EXPRESSION_HPP
#define SBROWSER2_XPATH_EXPRESSION_HPP


namespace dom::xpath {class xpath_expression;}

namespace dom::xpath {class xpath_result;}


class dom::xpath::xpath_expression
        : public virtual dom_object
{
public cpp_methods:
    auto evaluate(nodes::node* context_node, ext::number<ushort> type = 0, xpath_result* result = nullptr) -> xpath_result*;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_XPATH_EXPRESSION_HPP
