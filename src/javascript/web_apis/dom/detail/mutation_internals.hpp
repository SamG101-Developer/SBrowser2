#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

#include <memory>




#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(dom)
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
            std::unique_ptr<nodes::node> node,
            nodes::node* parent,
            const nodes::node* child)
            -> nodes::node*;

    auto pre_remove(
            const nodes::node* node,
            const nodes::node* parent)
            -> nodes::node*;

    // general mutations
    auto insert(
            std::unique_ptr<nodes::node>&& node,
            nodes::node* parent,
            const nodes::node* child,
            ext::boolean  suppress_observers_flag = false)
            -> nodes::node*;

    auto append(
            std::unique_ptr<nodes::node>&& node,
            nodes::node* parent)
            -> nodes::node*;

    auto replace(
            std::unique_ptr<nodes::node>&& node,
            const nodes::node* parent,
            nodes::node* child)
            -> nodes::node*;

    auto replace_all(
            std::unique_ptr<nodes::node>&& node,
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

    virtual ~registered_observer_t() = default;
};


struct dom::detail::transient_registered_observer_t : public registered_observer_t
{
    registered_observer_t* source = nullptr;
};


#endif //SBROWSER2_MUTATION_INTERNALS_HPP
