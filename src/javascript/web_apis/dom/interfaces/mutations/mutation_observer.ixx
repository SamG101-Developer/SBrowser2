module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.dom.mutation_observer;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, mutation_observer) final
        : public virtual dom_object
{
public typedefs:
    using mutation_observer_init_t = ext::map<ext::string, ext::any>;
    using mutation_callback_t = ext::unique_function<void(ext::vector<mutation_record*>&&, mutation_observer*)>;

public constructors:
    mutation_observer(mutation_callback_t&& callback);
    MAKE_PIMPL(mutation_observer);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto observe(node* target, mutation_observer_init_t&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<mutation_record*>;
};
