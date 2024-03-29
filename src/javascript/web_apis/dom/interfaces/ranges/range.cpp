module;
#include "ext/macros.hpp"


module apis.dom.range;
import apis.dom.window;
import apis.dom.detail;

import js.env.realms;


dom::range::range()
{
    INIT_PIMPL;
    ACCESS_PIMPL;

    auto e = js::env::env::current();
    d->start->node = e.cpp.global<window*>()->d_func()->document.get();
    d->end->node = e.cpp.global<window*>()->d_func()->document.get();
    d->start->offset = 0;
    d->end->offset = 0;
}


auto dom::range::set_start(node* new_container, ext::number<ulong> new_offset) -> void
{
    using enum dom::detail::dom_exception_error_t;
    throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [new_container] {return new_container->d_func()->parent_node.get();},
            u8"New start container must have a parent");

    // set the start of this range to the 'new_container' and 'new_offset' variables, by calling the detail method with
    // the same variables
    detail::set_start_or_end(this, new_container, new_offset, true);
}


auto dom::range::set_start_before(node* new_container) -> void
{
    using enum dom::detail::dom_exception_error_t;
    throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [new_container] {return new_container->d_func()->parent_node.get();},
            u8"New start container must have a parent");

    // set the start of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    auto parent_node = new_container->d_func()->parent_node.get();
    auto new_offset = detail::index(new_container);
    detail::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::range::set_start_after(node* new_container) -> void
{
    using enum dom::detail::dom_exception_error_t;
    throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [new_container] {return new_container->d_func()->parent_node.get();},
            u8"New start container must have a parent");

    // set the start of this range to be after the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    auto parent_node = new_container->d_func()->parent_node.get();
    auto new_offset = detail::index(new_container) + 1;
    detail::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::range::set_end(node* new_container, ext::number<ulong> new_offset) -> void
{
    using enum dom::detail::dom_exception_error_t;
    throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [new_container] {return new_container->d_func()->parent_node.get();},
            u8"New end container must have a parent");

    // set the end of this range to the 'new_container' and 'new_offset' variables, by calling the detail method with
    // the same variables
    detail::set_start_or_end(this, new_container, new_offset, false);
}


auto dom::range::set_end_before(node* new_container) -> void
{
    using enum dom::detail::dom_exception_error_t;
    throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [new_container] {return new_container->d_func()->parent_node.get();},
            u8"New end container must have a parent");

    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    auto parent_node = new_container->d_func()->parent_node.get();
    auto new_offset = detail::index(new_container);
    detail::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::range::set_end_after(
        node* new_container)
        -> void
{
    using enum dom::detail::dom_exception_error_t;
    throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [new_container] {return new_container->d_func()->parent_node.get();},
            u8"New end container must have a parent");

    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    auto parent_node = new_container->d_func()->parent_node.get();
    auto new_offset = detail::index(new_container) + 1;
    detail::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::range::insert_node(
        node* new_container)
        -> node*
{
    using enum dom::detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(range);

        detail::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                [this, d, new_container]
                {
                    return dom_multi_cast<comment*, processing_instruction*>(d->start->node.get())
                            || dom_cast<text*>(d->start->node.get()) && !new_container->d_func()->parent_node
                            || d->start->node.get() == new_container;
                },
                u8"Cannot insert a new container into a Range whose start node is a Comment/ProcessingInstruction, an orphaned Text node, or is the new container");

        // the 'reference_node' is the node that the 'new_container' will be inserted before; if the start container is a
        // Text node, then set the 'reference_node' to the start container (insert before all the text), otherwise the
        // child of the non-Text start container whose index is the offset (exact correct node)
        decltype(auto) reference_node = dom_cast<text*>(d->start->node.get())
                ? d->start->node
                : *ranges::first_where(d->start->node->d_func()->child_nodes | ranges::views::transform(&std::unique_ptr<node>::get), BIND_BACK(ext::cmp::eq, d->start->offset, &detail::index));

        // the 'parent_node' is the parent that the 'new_container' is going to be inserted into; if there is no
        // 'reference_node', then the parent is the start container, otherwise it's the reference node's parent node (the
        // 'new_container' will be inserted before the 'reference_node' into the 'parent_node'
        auto* parent_node = !reference_node
                ? d->start->node
                : reference_node->d_func()->parent_node;

        // if the reference node is a Text node, set it to everything after the start offset, otherwise if the reference
        // node is the 'new_container', then set it to the next sibling, otherwise leave it as it is
        reference_node = dom_cast<text*>(d->start->node.get())
                ? detail::split(dom_cast<text*>(d->start->node.get()), d->start->offset)
                : new_container == reference_node ? detail::next_sibling(reference_node) : reference_node;

        // the 'new_offset' is the length of the 'parent_node' if there is no 'reference_node', otherwise it's the index of
        // the 'reference_node'. adjust the 'new_offset' by the length of the 'new_container' if it's a DocumentFragment,
        // otherwise 1 (number of children being inserted)
        auto new_offset = !reference_node ? detail::length(parent_node) : detail::index(reference_node);
        new_offset += dynamic_cast<document_fragment*>(new_container) ? detail::length(new_container) : 1;

        // ensure that the 'new_container' can be inserted into the 'parent_node' before the 'reference_node', remove the
        // 'new_container' from its current parent (if it has a parent), and insert it into the 'parent_node' before the
        // 'reference_node'
        detail::ensure_pre_insertion_validity(new_container, parent_node, reference_node);
        detail::remove(new_container->d_func()->parent_node ? new_container : nullptr);
        detail::pre_insert(new_container, parent_node, reference_node);

        // if the range is currently collapsed, then set the end container and offset to the 'parent_node' and the
        // 'new_offset', so that the range maintains its collapsed state
        if (detail::is_range_collapsed(this))
            tuplet::tie(d->end->node, d->end->offset) = tuplet::make_tuple(parent_node, new_offset);

        return new_container;

    CE_REACTIONS_METHOD_EXE
}


auto dom::range::intersects_node(
        node* container)
        const -> ext::boolean
{
    ACCESS_PIMPL(const range);

    // return false if the range's root doesn't match the node's root, and return true if teh node doesn't have a parent
    // (orphaned nodes are always intercepted by all ranges)
    return_if(detail::root(container) != detail::root(this)) false;
    return_if(!container->d_func()->parent_node) true;

    // get the container's parent and offset, as they would be called multiple times otherwise, and save them under
    // variables
    auto container_parent = container->d_func()->parent_node.get();
    auto container_offset = detail::index(container);

    // if the node occurs before the end of the range, and after the start of the range, then it must be within the
    // range, and therefor is intersected by the range
    auto is_before_end  = detail::position_relative(container_parent, container_offset + 0, d->end->node.get()  , d->end->offset  ) == detail::BEFORE;
    auto is_after_start = detail::position_relative(container_parent, container_offset + 1, d->start->node.get(), d->start->offset) == detail::AFTER;
    return is_before_end && is_after_start;
}


auto dom::range::select_node(
        node* container)
        -> void
{
    ACCESS_PIMPL(const range);
    using enum dom::detail::dom_exception_error_t;
    throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [container] {return container->d_func()->parent_node.get();},
            u8"New container must have a parent");

    // get the index if the container sand save it as a variable to remove code duplication
    auto index = detail::index(container);

    // set the start and end containers to the parent of the container (so that the container is contained by the
    // range), and set the start offset to the index of the container (so the first node is the container), and set the
    // end offset to the index of the container + 1 (so the only node in the range is the container)
    auto parent_node = container->d_func()->parent_node.get();
    ext::tie(d->start->node, d->start->offset) = ext::make_tuple(parent_node, index);
    ext::tie(d->end->node  , d->end->offset  ) = ext::make_tuple(parent_node, index + 1);
}


auto dom::range::select_node_contents(
        node* container)
        -> void
{
    ACCESS_PIMPL(const range);
    using enum detail::dom_exception_error_t;

    // if the container is a DocumentType node, then throw an invalid node error
    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [container] {return !dom_multi_cast<document_type*>(container);},
            u8"Container can not be a DocumentType node");

    // set the start container to the 'container', and the start offset to 0; set the end container to the container,
    // and the offset to the length of the container this will mean that the range only contains the entire contents of
    // the range
    auto l = detail::length(container);
    ext::tie(d->start->node, d->start->offset) = ext::make_tuple(container, 0);
    ext::tie(d->end->node  , d->end->offset  ) = ext::make_tuple(container, l);
}


auto dom::range::compare_boundary_points(
        ext::number<ushort> how,
        dom::range* source_range)
        -> ext::number<short>
{
    ACCESS_PIMPL(range);
    using enum detail::dom_exception_error_t;

    // if the root of the 'source_range' doesn't this Range's root, then throw a wrong document error, because it isn't
    // possible to compare boundary points or ranges that are in different documents
    detail::throw_v8_exception<WRONG_DOCUMENT_ERR>(
            [this, source_range] {return detail::root(this) != detail::root(source_range);},
            u8"sourceRange's root must equal this Range's root");

    // set 'this_container/_offset' and 'that_container/_offset' to nullptr/0, to prepare them for the switch-case
    // block that determines their values based on the 'how' parameter
    auto [this_container, this_offset] = ext::make_tuple(static_cast<node*>(nullptr), ext::number<ulong>{});
    auto [that_container, that_offset] = ext::make_tuple(static_cast<node*>(nullptr), ext::number<ulong>{});

    // there are 4 different ways to compare the boundary points of 2 Range objects - the start and end of either Range
    // can be compared against the start or end of the other range, giving 4 different possibilities of comparison
    // methods
    switch(*how)
    {
        case(*START_TO_START): // start of that range to start of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(d->start->node.get(), d->start->offset);
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->d_func()->start->node.get(), source_range->d_func()->start->offset);
            break;

        case(*START_TO_END): // start of that range to end of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(d->end->node.get(), d->end->offset);
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->d_func()->start->node.get(), source_range->d_func()->start->offset);
            break;

        case(*END_TO_END): // end of that range to end of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(d->end->node.get(), d->end->offset);
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->d_func()->end->node.get(), source_range->d_func()->end->offset);
            break;

        case(*END_TO_START): // end of that range to start of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(d->start->node.get(), d->start->offset);
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->d_func()->end->node.get(), source_range->d_func()->end->offset);
            break;

        default: // if the 'how' value is invalid, throw a not supported error
            detail::throw_v8_exception<NOT_SUPPORTED_ERR>(NO_CONDITION, u8"The 'how' parameter must be 0 <= how <= 3");
            break;
    }

    // determine the position of 'this_container/_offset' compared to 'that_container/_offset' using the detail
    // comparison method
    return (short) detail::position_relative(this_container, this_offset, that_container, that_offset);
}


auto dom::range::compare_point(
        node* container,
        ext::number<ulong> offset)
        const -> ext::number<short>
{
    ACCESS_PIMPL(const range);
    using enum detail::dom_exception_error_t;

    detail::throw_v8_exception<WRONG_DOCUMENT_ERR>(
            [this, container_root = detail::root(container)] {return detail::root(this) != container_root;},
            u8"Container's root must equal this Range's root");

    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<document_type*>(container);},
            u8"Container can not be a DocumentType node");

    detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [offset, length = detail::length(container)] {return offset > length;},
            u8"Offset must be <= length of the node");

    return_if (detail::position_relative(container, offset, d->start->node.get(), d->start->offset) == detail::BEFORE) -1;
    return_if (detail::position_relative(container, offset, d->end->node.get()  , d->end->offset  ) == detail::AFTER ) 1;
    return 0;
}


auto dom::range::is_point_in_range(
        node* container,
        ext::number<ulong> offset)
        const -> ext::boolean
{
    ACCESS_PIMPL(const range);
    using enum detail::dom_exception_error_t;

    return_if (detail::root(this) != detail::root(container)) false;

    detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<document_type*>(container);},
            u8"Container can not be a DocumentType node");

    detail::throw_v8_exception<INDEX_SIZE_ERR>(
            [offset, length = detail::length(container)] {return offset > length;},
            u8"Offset must be <= length of the node");

    auto is_before_end  = detail::position_relative(container, offset, d->end->node.get()  , d->end->offset  ) == detail::BEFORE;
    auto is_after_start = detail::position_relative(container, offset, d->start->node.get(), d->start->offset) == detail::AFTER;
    return is_before_end && is_after_start;
}


auto dom::range::extract_contents() -> std::unique_ptr<document_fragment>
{
    using enum detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(range);

        // create a DocumentFragment node, and set its document to the same document that owns the 'start_container' of this
        // range; if this range is collapsed, then it doesn't contain anything, so return the empty DocumentFragment
        auto fragment = std::make_unique<document_fragment>();
        fragment->d_func()->node_document = d->start->node->d_func()->node_document.get();
        return_if (detail::is_range_collapsed(this)) fragment;

        // check if the start container of this Range is a textual container or not, ie is it / does it inherit the
        // CharacterData interface? (use the pointer as a boolean in if-statements)
        decltype(auto) textual_start_container = dom_cast<character_data*>(d->start->node.get());
        decltype(auto) textual_end_container   = dom_cast<character_data*>(d->end->node.get());

        // if the start container is textual, and the start and end containers are the same, then the Range is selecting a
        // textual node's contents, so clone the text from the 'start_offset' to the 'end_offset', append the extracted
        // text into 'fragment', and return 'fragment' - no more processing to do for single node contents extraction
        if (textual_start_container && textual_end_container && d->start->node.get() == d->end->node.get())
        {
            detail::copy_data(d->start->node.get(), fragment.get(), textual_start_container, d->start->offset, d->end->offset, true);
            return fragment;
        }

        // get the 'first_partially_contained_child', 'last_partially_contained_child', 'contained_children', by calling the
        // helper method, which determines these values using range filters
        auto [first_partially_contained_child, last_partially_contained_child, contained_children] =
                detail::get_range_containment_children(this, d->start->node.get(), d->end->node.get());

        // get the 'new_node' and 'new_offset', by calling the helper method, which determines theses values using the
        // containers and the 'start_offset'
        auto [new_node, new_offset] =
                detail::create_new_node_and_offset(d->start->node.get(), d->end->node.get(), d->start->offset);

        detail::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                [&contained_children] {return ranges::any_of(contained_children, &detail::is_document_type_node);},
                u8"Contained children cannot be DocumentType nodes");

        textual_start_container && dynamic_cast<character_data*>(first_partially_contained_child)
                ? detail::copy_data(
                        first_partially_contained_child, fragment.get(), textual_start_container, d->start->offset,
                        detail::length(d->start->node.get()), true)

                : detail::append_to_sub_fragment(
                        first_partially_contained_child, fragment.get(), d->start->node.get(), d->start->offset,
                        first_partially_contained_child, detail::length(first_partially_contained_child),
                        detail::EXTRACT);

        for (auto* contained_child: contained_children)
            detail::append(contained_child, fragment); // TODO : same node can't be in 2 places in tree (unique-ptr moved from somehwere?

        textual_end_container && dynamic_cast<character_data*>(last_partially_contained_child)
                ? detail::copy_data(
                        last_partially_contained_child, fragment.get(), textual_end_container, 0, d->end->offset, true)

                : detail::append_to_sub_fragment(
                        last_partially_contained_child, fragment.get(), last_partially_contained_child, 0, d->end->node.get(), d->end->offset, detail::EXTRACT);

        ext::tie(d->start->node, d->start->offset) = ext::make_tuple(new_node, new_offset);
        ext::tie(d->end->node  , d->end->offset  ) = ext::make_tuple(new_node, new_offset);
        return fragment;
    CE_REACTIONS_METHOD_EXE
}


auto dom::range::clone_contents() -> std::unique_ptr<document_fragment>
{
    using enum detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(range);

        // create a DocumentFragment node, and set its document to the same document that owns the 'start_container' of this
        // range; if this range is collapsed, then it doesn't contain anything, so return the empty DocumentFragment
        auto fragment = std::make_unique<document_fragment>();
        fragment->d_func()->node_document = d->start->node->d_func()->node_document.get();
        return_if (detail::is_range_collapsed(this)) fragment;

        // check if the start container of this Range is a textual container or not, ie is it / does it inherit the
        // CharacterData interface? (use the pointer as a boolean in if-statements)
        decltype(auto) textual_start_container = dom_cast<character_data*>(d->start->node.get());
        decltype(auto) textual_end_container   = dom_cast<character_data*>(d->end->node.get()  );

        // if the start container is textual, and the start and end containers are the same, then the Range is selecting a
        // textual node's contents, so clone the text from the 'start_offset' to the 'end_offset', append the extracted
        // text into 'fragment', and return 'fragment' - no more processing to do for single node contents extraction
        if (textual_start_container && textual_end_container && d->start->node.get() == d->end->node.get())
        {
            detail::copy_data(d->start->node.get(), fragment.get(), textual_start_container, d->start->offset, d->end->offset, false);
            return fragment;
        }

        // get the 'first_partially_contained_child', 'last_partially_contained_child', 'contained_children', by calling the
        // helper method, which determines these values using range filters
        auto [first_partially_contained_child, last_partially_contained_child, contained_children] =
                detail::get_range_containment_children(this, d->start->node.get(), d->end->node.get());

        detail::throw_v8_exception<HIERARCHY_REQUEST_ERR>(
                [contained_children] {return ranges::any_of(contained_children, &detail::is_document_type_node);},
                u8"Contained children cannot be DocumentType nodes");

        textual_start_container && dynamic_cast<character_data*>(first_partially_contained_child)
                ? detail::copy_data(
                        first_partially_contained_child, fragment.get(), textual_start_container, d->start->offset,
                        detail::length(d->start->node.get()), true)

                : detail::append_to_sub_fragment(
                        first_partially_contained_child, fragment.get(), d->start->node.get(), d->start->offset,
                        first_partially_contained_child, detail::length(first_partially_contained_child),
                        detail::CLONE);

        for (auto* contained_child: contained_children)
            detail::append(contained_child->clone_node(true), fragment.get());

        textual_end_container && dynamic_cast<character_data*>(last_partially_contained_child)
                ? detail::copy_data(last_partially_contained_child, fragment.get(), textual_end_container, 0, d->end->offset, true)
                : detail::append_to_sub_fragment(last_partially_contained_child, fragment.get(), last_partially_contained_child, 0, d->end->node.get(), d->end->offset, detail::CLONE);

        return fragment;
    CE_REACTIONS_METHOD_EXE
}


auto dom::range::delete_contents() -> void
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(range);
        return_if(detail::is_range_collapsed(this)) static_cast<document_fragment*>(nullptr);

        // check if the start container of this Range is a textual container or not, ie is it / does it inherit the
        // CharacterData interface? (use the pointer as a boolean in if-statements)
        decltype(auto) textual_start_container = dom_cast<character_data*>(d->start->node.get());
        decltype(auto) textual_end_container   = dom_cast<character_data*>(d->end->node.get()  );

        // if the start container is textual, and the start and end containers are the same, then the Range is selecting a
        // textual node's contents, so clone the text from the 'start_offset' to the 'end_offset', append the extracted
        // text into 'fragment', and return 'fragment' - no more processing to do for single node contents extraction
        if (textual_start_container && textual_end_container && d->start->node.get() == d->end->node.get())
            detail::replace_data(textual_start_container, d->start->offset, d->end->offset - d->start->offset, u"");

        auto nodes_to_remove = detail::descendants(detail::root(this))
                | ranges::views::filter([this](node* node) {return  detail::contains(node, this);})
                | ranges::views::filter([this](node* node) {return !detail::contains(node->d_func()->parent_node.get(), this);});

        // get the 'new_node' and 'new_offset', by calling the helper method, which determines theses values using the
        // containers and the 'start_offset'
        auto [new_node, new_offset] =
                detail::create_new_node_and_offset(d->start->node.get(), d->end->node.get(), d->start->offset);

        if (textual_start_container)
            detail::replace_data(textual_start_container, d->start->offset, detail::length(d->start->node.get()), u"");

        for (const auto& node_to_remove: nodes_to_remove)
            detail::remove(node_to_remove);

        if (textual_end_container)
            detail::replace_data(textual_end_container, 0, d->end->offset, u"");

        ext::tie(d->start->node, d->start->offset) = ext::make_tuple(new_node, new_offset);
        ext::tie(d->end->node  , d->end->offset  ) = ext::make_tuple(new_node, new_offset);
    CE_REACTIONS_METHOD_EXE
}


auto dom::range::surround_contents(node* parent) -> std::unique_ptr<document_fragment>
{
    using enum dom::detail::dom_exception_error_t;

    CE_REACTIONS_METHOD_DEF
        detail::throw_v8_exception<INVALID_STATE_ERR>( // TODO
                [this]
                {
                    return ranges::any_of(
                            detail::descendants(detail::root(this)) | ranges::views::filter(BIND_BACK(detail::partially_contains, this)),
                            dom_cast<text*>);
                },
                u8"Cannot surround a Range that partially contains non-Text nodes");

        detail::throw_v8_exception<INVALID_NODE_TYPE_ERR>(
                [parent] {return dom_multi_cast<document*, document_type*, document_fragment*>(parent);},
                u8"New parent can not be a Document, DocumentType or DocumentFragment");

        decltype(auto) fragment = extract_contents();
        detail::replace_all(nullptr, parent);
        detail::append(std::move(fragment), parent);
        insert_node(parent);
        select_node(parent);

        return fragment;
    CE_REACTIONS_METHOD_EXE
}


auto dom::range::collapse(
        ext::boolean to_start)
        -> void
{
    ACCESS_PIMPL(range);

    to_start
            ? ext::tie(d->end->node, d->end->offset)     = ext::make_tuple(d->start->node.get(), d->start->offset)
            : ext::tie(d->start->node, d->start->offset) = ext::make_tuple(d->end->node.get()  , d->end->offset  );
}


auto dom::range::clone_range()
        const -> std::unique_ptr<range>
{
    ACCESS_PIMPL(const range);
    auto new_range = std::make_unique<range>();
    ext::tie(new_range->d_func()->start->node, new_range->d_func()->start->offset) = ext::make_tuple(d->start->node.get(), d->start->offset);
    ext::tie(new_range->d_func()->end->node  , new_range->d_func()->end->offset  ) = ext::make_tuple(d->end->node.get()  , d->end->offset  );
    return new_range;
}


auto dom::range::get_common_ancestor_container() const -> node*
{
    ACCESS_PIMPL(const range);
    return detail::common_ancestor(d->start->node.get(), d->end->node.get());
}


dom::range::operator ext::string() const
{
    ACCESS_PIMPL(const range);
    auto s = ext::string{};
    decltype(auto) textual_start_container = dom_cast<character_data*>(d->start->node.get());
    decltype(auto) textual_end_container   = dom_cast<character_data*>(d->end->node.get());

    if (textual_start_container && textual_end_container && d->start->node.get() == d->end->node.get())
        return detail::substring_data(textual_start_container, d->start->offset, d->end->offset - d->start->offset);

    if (textual_start_container)
        s += detail::substring_data(textual_start_container, d->start->offset, detail::length(textual_start_container) - d->start->offset);

    s += detail::descendant_text_nodes(detail::root(this))
            | ranges::views::filter(BIND_BACK(detail::contains, this))
            | ranges::views::transform_to_attr(&text_private::data, ext::get_pimpl)
            | ranges::to<ext::string>();

    if (textual_end_container)
        s += detail::substring_data(textual_end_container, 0, d->end->offset);
}


auto dom::range::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .ctor<>()
        .inherit<abstract_range>()
        .static_("START_TO_START", range::START_TO_START)
        .static_("START_TO_END", range::START_TO_END)
        .static_("END_TO_END", range::END_TO_END)
        .static_("END_TO_START", range::END_TO_START)
        .function("setStart", &range::set_start)
        .function("setStartAfter", &range::set_start_after)
        .function("setStartBefore", &range::set_start_before)
        .function("setEnd", &range::set_end)
        .function("setEndAfter", &range::set_end_after)
        .function("setEndBefore", &range::set_end_before)
        .function("insertNode", &range::insert_node)
        .function("intersectsNode", &range::intersects_node)
        .function("selectNode", &range::select_node)
        .function("selectNodeContents", &range::select_node_contents)
        .function("compareBoundaryPoints", &range::compare_boundary_points)
        .function("comparePoint", &range::compare_point)
        .function("extractContents", &range::extract_contents)
        .function("cloneContents", &range::clone_contents)
        .function("deleteContents", &range::delete_contents)
        .function("surroundContents", &range::surround_contents)
        .function("collapse", &range::collapse)
        .function("cloneRange", &range::clone_range)
        .function("isPointInRange", &range::is_point_in_range)
        .function("toJSON", &range::operator ext::string)
        .property("commonAncestorContainer", &range::get_common_ancestor_container)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
