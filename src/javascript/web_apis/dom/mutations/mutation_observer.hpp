#ifndef SBROWSER2_MUTATION_OBSERVER_HPP
#define SBROWSER2_MUTATION_OBSERVER_HPP

#include "dom_object.hpp"
namespace dom::mutations {class mutation_observer;}

#include "ext/map.hpp"
#include "ext/functional.hpp"
#include "ext/queue.hpp"
#include "ext/vector.hpp"
namespace dom::mutations {class mutation_record;}

namespace dom::detail {auto notify_mutation_observers() -> void;}


class dom::mutations::mutation_observer
        : public virtual dom_object
{
public friends:
    friend auto dom::detail::notify_mutation_observers()
            -> void;

public aliases:
    using mutation_callback_t = ext::function<void(const ext::vector<mutation_record*>&, mutation_observer*)>;

public constructors:
    DOM_CTORS(mutation_observer);
    mutation_observer() = default;
    mutation_observer(mutation_callback_t&& callback);

public js_methods:
    auto observe(const nodes::node* target, ext::map<ext::string, ext::any>&& options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<mutation_record*>;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_properties:
    mutation_callback_t m_callback;
    std::unique_ptr<ext::vector<nodes::node*>> m_node_list;
    std::unique_ptr<ext::queue<mutation_record*>> m_record_queue;
};


#endif //SBROWSER2_MUTATION_OBSERVER_HPP
