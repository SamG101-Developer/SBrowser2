#pragma once
#ifndef SBROWSER2_XPATH_EVALUATOR_HPP
#define SBROWSER2_XPATH_EVALUATOR_HPP


namespace dom::xpath {class xpath_evaluator;}

class dom::xpath::xpath_evaluator
        : public xpath::xpath_evaluator_base
{
public constructors:
    xpath_evaluator() = default;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_XPATH_EVALUATOR_HPP
