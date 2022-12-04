#ifndef SBROWSER2_MUTATION_OBSERVER_HPP
#define SBROWSER2_MUTATION_OBSERVER_HPP

#include "dom_object.hpp"
namespace dom::mutations {class mutation_observer;}
namespace dom::mutations {class mutation_observer_private;}




#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::mutations {class mutation_record;}


class dom::mutations::mutation_observer
        : public virtual dom_object
{
public constructors:
    mutation_observer(detail::mutation_callback_t&& callback);
    MAKE_PIMPL(mutation_observer);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto observe(nodes::node* target, detail::mutation_observer_init_t&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<mutation_record*>;
};


#endif //SBROWSER2_MUTATION_OBSERVER_HPP
