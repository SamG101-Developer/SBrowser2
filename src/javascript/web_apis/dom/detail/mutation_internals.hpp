#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

#include "ext/boolean.hpp"
namespace dom::nodes {class node;}


namespace dom::detail::mutation_internals
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
            ext::boolean_view suppress_observers_flag = false)
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
            ext::boolean_view suppress_observers_flag = false)
            -> nodes::node*;
}


#endif //SBROWSER2_MUTATION_INTERNALS_HPP
