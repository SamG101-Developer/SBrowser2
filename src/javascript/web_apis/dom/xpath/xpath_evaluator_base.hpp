#pragma once
#ifndef SBROWSER2_XPATH_EVALUATOR_BASE_HPP
#define SBROWSER2_XPATH_EVALUATOR_BASE_HPP

#include "dom_object.hpp"
namespace dom::xpath {class xpath_evaluator_base;}

namespace dom::xpath {class xpath_expression;}
namespace dom::xpath {class xpath_ns_resolver;}
namespace dom::xpath {class xpath_result;}


class dom::xpath::xpath_evaluator_base
        : public virtual web_apis::dom_object
{
public js_methods:
    auto create_expression(ext::string expression, xpath_ns_resolver* resolver = nullptr) -> xpath_expression;
    auto create_ns_resolver(nodes::node* node_resolver) -> xpath_ns_resolver;
    auto evaluate(ext::string_view expression, nodes::node* context_node, xpath_ns_resolver* resolver = nullptr, ext::number<ushort> type = 0, xpath_result* result = nullptr) -> xpath_result;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_XPATH_EVALUATOR_BASE_HPP
