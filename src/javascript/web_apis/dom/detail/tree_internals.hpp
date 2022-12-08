#ifndef SBROWSER2_TREE_INTERNALS_HPP
#define SBROWSER2_TREE_INTERNALS_HPP


namespace dom::detail
{
    auto document_element(
            const nodes::document* document)
            -> nodes::element*;
}


#endif //SBROWSER2_TREE_INTERNALS_HPP
