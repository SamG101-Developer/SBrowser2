#ifndef SBROWSER2_MUTATION_OBSERVER_HPP
#define SBROWSER2_MUTATION_OBSERVER_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mutations {class mutation_observer;}

#include <ext/map.hpp>
#include <ext/vector.hpp>
namespace dom::mutations {class mutation_record;}


class dom::mutations::mutation_observer
        : public virtual web_apis::dom_object
{
public aliases:
    using mutation_callback_t = std::function<void(const ext::vector<mutation_record*>&, mutation_observer*)>;

public constructors:
    mutation_observer() = default;
    mutation_observer(mutation_callback_t&& callback);

public js_methods:
    auto observe(const nodes::node* target, ext::string_any_map_view options = {}) -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<mutation_record*>;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    mutation_callback_t m_callback;
    std::unique_ptr<ext::vector<nodes::node*>> m_node_list;
    std::unique_ptr<std::queue<mutation_record>> m_record_queue;
};


#endif //SBROWSER2_MUTATION_OBSERVER_HPP
