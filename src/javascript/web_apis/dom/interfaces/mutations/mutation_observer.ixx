module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.dom.mutation_observer;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, mutation_observer) final
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(mutation_observer);
    MAKE_V8_AVAILABLE(WINDOW);
    mutation_observer(this_private_t::mutation_callback_t&& callback);

private js_methods:
    auto observe(node* target, this_private_t::mutation_observer_init_t&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<mutation_record*>;
};
