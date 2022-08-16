#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

#include <memory>
#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "dom/_typedefs.hpp"
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
            const ext::boolean& suppress_observers_flag = false)
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
            const ext::boolean& suppress_observers_flag = false)
            -> nodes::node*;
}


struct dom::detail::registered_observer_t
{
    std::unique_ptr<mutations::mutation_observer> observer;
    ext::map<ext::string, ext::any> options;
    virtual registered_observer_t() = default;
};


struct dom::detail::transient_registered_observer_t : public registered_observer_t
{
    std::unique_ptr<registered_observer_t> source;
};



#endif //SBROWSER2_MUTATION_INTERNALS_HPP
