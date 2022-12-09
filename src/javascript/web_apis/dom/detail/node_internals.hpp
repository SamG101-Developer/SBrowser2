#ifndef SBROWSER2_NODE_INTERNALS_HPP
#define SBROWSER2_NODE_INTERNALS_HPP



namespace dom::detail
{
    // node manipulation
    template <ext::inherit<nodes::node> T>
    auto clone(
            T* node,
            nodes::document* document = nullptr,
            ext::boolean deep = false)
            -> std::unique_ptr<T>;


}


#endif //SBROWSER2_NODE_INTERNALS_HPP
