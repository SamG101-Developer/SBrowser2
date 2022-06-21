#ifndef SBROWSER2_MUTATION_INTERNALS_HPP
#define SBROWSER2_MUTATION_INTERNALS_HPP

namespace dom::nodes {class node;}


namespace dom::detail::mutation_internals
{
    // common checks across multiple methods / validity checks
    static auto common_checks(
            nodes::node* node,
            nodes::node* parent,
            const nodes::node* child)
            -> void;

    static auto ensure_pre_insertion_validity(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child)
            -> void;

    // pre-insertion and -removal
    static auto pre_insert(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child)
            -> nodes::node*;

    static auto pre_remove(
            nodes::node* node,
            const nodes::node* parent)
            -> nodes::node*;

    // general mutations
    static auto insert(
            nodes::node* node,
            const nodes::node* parent,
            const nodes::node* child,
            bool suppress_observers_flag = false)
            -> nodes::node*;

    static auto append(
            nodes::node* node,
            nodes::node* parent)
            -> nodes::node*;

    static auto replace(
            nodes::node* node,
            nodes::node* parent,
            nodes::node* child)
            -> nodes::node*;

    static auto remove(
            nodes::node* node,
            bool suppress_observers_flag = false)
            -> nodes::node*;

    static auto replace_all(
            nodes::node* node,
            nodes::node* parent)
            -> void;
}


#endif //SBROWSER2_MUTATION_INTERNALS_HPP
