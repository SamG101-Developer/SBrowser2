module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <function2/function2.hpp>

export module apis.dom.mutation_observer;
import apis._.dom_object;
import ext.any;
import ext.functional;
import ext.map;
import ext.string;
import ext.tuple;
import ext.type_traits;
import ext.vector;
import js.env.module_type;

namespace dom {class mutation_record; class node;}


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
