#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

#include <memory>
#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/queue.hpp"
#include "ext/string.hpp"
#include USE_INNER_TYPES(dom)
namespace dom::nodes {class node;}
namespace dom::mutations {class mutation_observer;}


namespace dom::detail
{
    // common checks across multiple methods / validity checks
    auto common_checks(
            const nodes::node* node,
            const nodes::node* parent,
            const nodes::node* child)
            -> void;

    auto ensure_pre_insertion_validity(
            const nodes::node* node,
            const nodes::node* parent,
            const nodes::node* child)
            -> void;

    // pre-insertion and -removal
    auto pre_insert(
            const nodes::node* node,
            const nodes::node* parent,
            const nodes::node* child)
            -> nodes::node*;

    auto pre_remove(
            const nodes::node* node,
            const nodes::node* parent)
            -> nodes::node*;

    // general mutations
    auto insert(
            const nodes::node* node,
            const nodes::node* parent,
            const nodes::node* child,
            ext::boolean  suppress_observers_flag = false)
            -> nodes::node*;

    auto append(
            const nodes::node* node,
            const nodes::node* parent)
            -> nodes::node*;

    auto replace(
            const nodes::node* node,
            const nodes::node* parent,
            nodes::node* child)
            -> nodes::node*;

    auto replace_all(
            const nodes::node* node,
            const nodes::node* parent)
            -> void;

    auto remove(
            const nodes::node* node,
            ext::boolean  suppress_observers_flag = false)
            -> nodes::node*;
}


struct dom::detail::registered_observer_t
{
    mutations::mutation_observer* observer = nullptr;
    ext::map<ext::string, ext::any> options;
};


struct dom::detail::transient_registered_observer_t : public registered_observer_t
{
    registered_observer_t* source = nullptr;
};


struct dom::detail::mutation_observer_t
{
    mutation_callback_t m_callback;
    ext::vector<nodes::node*> m_node_list;
    ext::queue<mutations::mutation_record*> m_record_queue;
};



#endif //SBROWSER2_MUTATION_INTERNALS_HPP
