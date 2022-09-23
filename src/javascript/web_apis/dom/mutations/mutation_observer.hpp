#ifndef SBROWSER2_MUTATION_OBSERVER_HPP
#define SBROWSER2_MUTATION_OBSERVER_HPP

#include "dom_object.hpp"
namespace dom::mutations {class mutation_observer;}

#include "ext/map.hpp"
#include "ext/functional.hpp"
#include "ext/queue.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::mutations {class mutation_record;}

#include "dom/mutations/mutation_observer_private.hpp"


class dom::mutations::mutation_observer
        : public virtual dom_object
{
public constructors:
    mutation_observer() = default;
    mutation_observer(detail::mutation_callback_t&& callback);
    MAKE_PIMPL(mutation_observer);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto observe(const nodes::node* target, ext::map<ext::string, ext::any>&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<mutation_record*>;
};


#endif //SBROWSER2_MUTATION_OBSERVER_HPP
