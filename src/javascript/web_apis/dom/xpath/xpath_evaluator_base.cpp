#include "xpath_evaluator_base.hpp"

#include <web_apis/dom/xpath/xpath_expression.hpp>
#include <web_apis/dom/xpath/xpath_ns_resolver.hpp>
#include <web_apis/dom/xpath/xpath_result.hpp>


auto dom::xpath::xpath_evaluator_base::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<xpath_evaluator_base>{isolate}
            .inherit<dom_object>()
            .function("createExpression", &xpath_evaluator_base::create_expression)
            .function("createNSResolver", &xpath_evaluator_base::create_ns_resolver)
            .function("evaluate", &xpath_evaluator_base::evaluate)
            .auto_wrap_objects();
}
