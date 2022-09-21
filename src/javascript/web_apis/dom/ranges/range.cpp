#include "range.hpp"

#include "ext/boolean.hpp"
#include "ext/casting.hpp"
#include "ext/functional.hpp"
#include "ext/tuple.hpp"
#include "ext/ranges.hpp"

#include "javascript/environment/realms_2.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/detail/range_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include "dom/nodes/character_data.hpp"
#include "dom/nodes/comment.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_fragment.hpp"
#include "dom/nodes/document_type.hpp"
#include "dom/nodes/processing_instruction.hpp"
#include "dom/nodes/text.hpp"
#include "dom/nodes/window.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>


dom::node_ranges::range::range()
{
    bind_get(common_ancestor_container);

    JS_REALM_GET_CURRENT
    start_container = v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object)->document();
    end_container   = v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object)->document();
    start_offset    = 0;
    end_offset      = 0;

    m_root = nullptr;
}


auto dom::node_ranges::range::set_start(
        nodes::node* new_container,
        ext::number<ulong> new_offset)
        -> void
{
    // set the start of this range to the 'new_container' and 'new_offset' variables, by calling the detail method with
    // the same variables
    detail::set_start_or_end(this, new_container, new_offset, true);
}


auto dom::node_ranges::range::set_start_before(
        nodes::node* new_container)
        -> void
{
    // set the start of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::index(new_container);
    detail::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::node_ranges::range::set_start_after(
        nodes::node* new_container)
        -> void
{
    // set the start of this range to be after the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::index(new_container) + 1;
    detail::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::node_ranges::range::set_end(
        nodes::node* new_container,
        ext::number<ulong> new_offset)
        -> void
{
    // set the end of this range to the 'new_container' and 'new_offset' variables, by calling the detail method with
    // the same variables
    detail::set_start_or_end(this, new_container, new_offset, false);
}


auto dom::node_ranges::range::set_end_before(
        nodes::node* new_container)
        -> void
{
    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::index(new_container);
    detail::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::node_ranges::range::set_end_after(
        nodes::node* new_container)
        -> void
{
    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::index(new_container) + 1;
    detail::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::node_ranges::range::insert_node(
        nodes::node* new_container)
        -> nodes::node*
{
    CE_REACTIONS_METHOD_DEF
        detail::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [this, new_container]{return ext::multi_cast<nodes::comment*, nodes::processing_instruction*>(start_container())
                        || dynamic_cast<nodes::text*>(start_container()) && !new_container->parent_node()
                        || start_container() == new_container;},
                "Cannot insert a new container into a Range whose start node is a Comment/ProcessingInstruction, an orphaned Text node, or is the new container");

        // the 'reference_node' is the node that the 'new_container' will be inserted before; if the start container is a
        // Text node, then set the 'reference_node' to the start container (insert before all the text), otherwise the
        // child of the non-Text start container whose index is the offset (exact correct node)
        auto* reference_node = dynamic_cast<nodes::text*>(start_container())
                ? start_container()
                : *ranges::first_where(*start_container()->child_nodes(), [this](nodes::node* child_node) {return detail::index(child_node) == start_offset();});

        // the 'parent_node' is the parent that the 'new_container' is going to be inserted into; if there is no
        // 'reference_node', then the parent is the start container, otherwise it's the reference node's parent node (the
        // 'new_container' will be inserted before the 'reference_node' into the 'parent_node'
        auto* parent_node = !reference_node
                ? start_container()
                : reference_node->parent_node();

        // if the reference node is a Text node, set it to everything after the start offset, otherwise if the reference
        // node is the 'new_container', then set it to the next sibling, otherwise leave it as it is
        reference_node = dynamic_cast<nodes::text*>(start_container())
                ? &detail::split(dynamic_cast<nodes::text*>(start_container()), start_offset())
                : new_container == reference_node ? reference_node->next_sibling() : reference_node;

        // the 'new_offset' is the length of the 'parent_node' if there is no 'reference_node', otherwise it's the index of
        // the 'reference_node'. adjust the 'new_offset' by the length of the 'new_container' if it's a DocumentFragment,
        // otherwise 1 (number of children being inserted)
        auto new_offset = !reference_node ? detail::length(parent_node) : detail::index(reference_node);
        new_offset += dynamic_cast<nodes::document_fragment*>(new_container) ? detail::length(new_container) : 1;

        // ensure that the 'new_container' can be inserted into the 'parent_node' before the 'reference_node', remove the
        // 'new_container' from its current parent (if it has a parent), and insert it into the 'parent_node' before the
        // 'reference_node'
        detail::ensure_pre_insertion_validity(new_container, parent_node, reference_node);
        detail::remove(new_container->parent_node() ? new_container : nullptr);
        detail::pre_insert(new_container, parent_node, reference_node);

        // if the range is currently collapsed, then set the end container and offset to the 'parent_node' and the
        // 'new_offset', so that the range maintains its collapsed state
        if (collapsed())
            tuplet::tie(end_container, end_offset) = tuplet::make_tuple(parent_node, new_offset);

        return new_container;

    CE_REACTIONS_METHOD_EXE
}


auto dom::node_ranges::range::intersects_node(
        nodes::node* container)
        const -> ext::boolean
{
    // return false if the range's root doesn't match the node's root, and return true if teh node doesn't have a parent
    // (orphaned nodes are always intercepted by all ranges)
    return_if(detail::root(container) != m_root) false;
    return_if(!container->parent_node()) true;

    // get the container's parent and offset, as they would be called multiple times otherwise, and save them under
    // variables
    auto container_parent = container->parent_node();
    auto container_offset = detail::index(container);

    // if the node occurs before the end of the range, and after the start of the range, then it must be within the
    // range, and therefor is intersected by the range
    auto is_before_end  = detail::position_relative(container_parent, container_offset + 0, end_container()  , end_offset()  ) == detail::BEFORE;
    auto is_after_start = detail::position_relative(container_parent, container_offset + 1, start_container(), start_offset()) == detail::AFTER;
    return is_before_end && is_after_start;
}


auto dom::node_ranges::range::select_node(
        nodes::node* container)
        -> void
{
    verify_parent_exists(container);

    // get the index if the container sand save it as a variable to remove code duplication
    auto index = detail::index(container);

    // set the start and end containers to the parent of the container (so that the container is contained by the
    // range), and set the start offset to the index of the container (so the first node is the container), and set the
    // end offset to the index of the container + 1 (so the only node in the range is the container)
    auto parent_node = container->parent_node();
    ext::tie(start_container, start_offset) = ext::make_tuple(parent_node, index);
    ext::tie(end_container, end_offset) = ext::make_tuple(parent_node, index + 1);
}


auto dom::node_ranges::range::select_node_contents(
        nodes::node* container)
        -> void
{
    // if the container is a DocumentType node, then throw an invalid node error
    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<nodes::document_type*>(container);},
            "Container can not be a DocumentType node");

    // set the start container to the 'container', and the start offset to 0; set the end container to the container,
    // and the offset to the length of the container this will mean that the range only contains the entire contents of
    // the range
    auto l = detail::length(container);
    ext::tie(start_container, start_offset) = ext::make_tuple(container, 0);
    ext::tie(end_container, end_offset)     = ext::make_tuple(container, l);
}


auto dom::node_ranges::range::compare_boundary_points(
        ext::number<ushort> how,
        dom::node_ranges::range* source_range)
        -> ext::number<short>
{
    // if the root of the 'source_range' doesn't this Range's root, then throw a wrong document error, because it isn't
    // possible to compare boundary points or ranges that are in different documents
    detail::throw_v8_exception_formatted<WRONG_DOCUMENT_ERR>(
            [this, source_range] {return m_root != source_range->m_root;},
            "sourceRange's root must equal this Range's root");

    // set 'this_container/_offset' and 'that_container/_offset' to nullptr/0, to prepare them for the switch-case
    // block that determines their values based on the 'how' parameter
    auto [this_container, this_offset] = ext::make_tuple(static_cast<nodes::node*>(nullptr), ext::number<ulong>{});
    auto [that_container, that_offset] = ext::make_tuple(static_cast<nodes::node*>(nullptr), ext::number<ulong>{});

    // there are 4 different ways to compare the boundary points of 2 Range objects - the start and end of either Range
    // can be compared against the start or end of the other range, giving 4 different possibilities of comparison
    // methods
    switch(*how)
    {
        case(*START_TO_START): // start of that range to start of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(start_container(), start_offset());
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->start_container(), source_range->start_offset());
            break;

        case(*START_TO_END): // start of that range to end of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(end_container(), end_offset());
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->start_container(), source_range->start_offset());
            break;

        case(*END_TO_END): // end of that range to end of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(end_container(), end_offset());
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->end_container(), source_range->end_offset());
            break;

        case(*END_TO_START): // end of that range to start of this range
            ext::tie(this_container, this_offset) = ext::make_tuple(start_container(), start_offset());
            ext::tie(that_container, that_offset) = ext::make_tuple(source_range->end_container(), source_range->end_offset());
            break;

        default: // if the 'how' value is invalid, throw a not supported error
            detail::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(NO_CONDITION, "The 'how' parameter must be 0 <= how <= 3");
            break;
    }

    // determine the position of 'this_container/_offset' compared to 'that_container/_offset' using the detail
    // comparison method
    return (short) detail::position_relative(this_container, this_offset, that_container, that_offset);
}


auto dom::node_ranges::range::compare_point(
        nodes::node* container,
        ext::number<ulong> offset)
        const -> ext::number<short>
{
    detail::throw_v8_exception_formatted<WRONG_DOCUMENT_ERR>(
            [this, container_root = detail::root(container)] {return m_root != container_root;},
            "Container's root must equal this Range's root");

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<nodes::document_type*>(container);},
            "Container can not be a DocumentType node");

    detail::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [offset, length = detail::length(container)] {return offset > length;},
            "Offset must be <= length of the node");

    return_if(detail::position_relative(container, offset, start_container(), start_offset()) == detail::BEFORE) -1;
    return_if(detail::position_relative(container, offset, end_container(), end_offset()) == detail::AFTER) 1;
    return 0;
}


auto dom::node_ranges::range::is_point_in_range(
        nodes::node* container,
        ext::number<ulong> offset)
        const -> ext::boolean
{
    return_if(m_root != detail::root(container)) false;

    detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<nodes::document_type*>(container);},
            "Container can not be a DocumentType node");

    detail::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [offset, length = detail::length(container)] {return offset > length;},
            "Offset must be <= length of the node");

    auto is_before_end  = detail::position_relative(container, offset, end_container()  , end_offset()  ) == detail::BEFORE;
    auto is_after_start = detail::position_relative(container, offset, start_container(), start_offset()) == detail::AFTER;
    return is_before_end && is_after_start;
}


auto dom::node_ranges::range::extract_contents()
        -> nodes::document_fragment*
{
    CE_REACTIONS_METHOD_DEF
        // create a DocumentFragment node, and set its document to the same document that owns the 'start_container' of this
        // range; if this range is collapsed, then it doesn't contain anything, so return the empty DocumentFragment
        auto fragment = new nodes::document_fragment{};
        fragment->owner_document = start_container()->owner_document();
        return_if(collapsed()) fragment;

        // check if the start container of this Range is a textual container or not, ie is it / does it inherit the
        // CharacterData interface? (use the pointer as a boolean in if-statements)
        auto* textual_start_container = dynamic_cast<nodes::character_data*>(start_container());
        auto* textual_end_container   = dynamic_cast<nodes::character_data*>(end_container()  );

        // if the start container is textual, and the start and end containers are the same, then the Range is selecting a
        // textual node's contents, so clone the text from the 'start_offset' to the 'end_offset', append the extracted
        // text into 'fragment', and return 'fragment' - no more processing to do for single node contents extraction
        if (textual_start_container && textual_end_container && start_container() == end_container())
        {
            detail::copy_data(start_container(), fragment, textual_start_container, start_offset(), end_offset(), true);
            return fragment;
        }

        // get the 'first_partially_contained_child', 'last_partially_contained_child', 'contained_children', by calling the
        // helper method, which determines these values using range filters
        auto [first_partially_contained_child, last_partially_contained_child, contained_children] =
                detail::get_range_containment_children(this, start_container(), end_container());

        // get the 'new_node' and 'new_offset', by calling the helper method, which determines theses values using the
        // containers and the 'start_offset'
        auto [new_node, new_offset] =
                detail::create_new_node_and_offset(start_container(), end_container(), start_offset());

        detail::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [contained_children] {return ranges::any_of(contained_children, ext::bind_front(detail::is_document_type_node));},
                "Contained children cannot be DocumentType nodes");

        textual_start_container && dynamic_cast<nodes::character_data*>(first_partially_contained_child)
                ? detail::copy_data(
                        first_partially_contained_child, fragment, textual_start_container, start_offset(),
                        detail::length(start_container()), true)

                : detail::append_to_sub_fragment(
                        first_partially_contained_child, fragment, start_container(), start_offset(),
                        first_partially_contained_child, detail::length(first_partially_contained_child),
                        detail::EXTRACT);

        for (auto* contained_child: contained_children)
            detail::append(contained_child, fragment);

        textual_end_container && dynamic_cast<nodes::character_data*>(last_partially_contained_child)
                ? detail::copy_data(
                        last_partially_contained_child, fragment, textual_end_container, 0, end_offset(), true)

                : detail::append_to_sub_fragment(
                        last_partially_contained_child, fragment, last_partially_contained_child, 0, end_container(),
                        end_offset(), detail::EXTRACT);

        ext::tie(start_container, start_offset) = ext::make_tuple(new_node, new_offset);
        ext::tie(end_container  , end_offset  ) = ext::make_tuple(new_node, new_offset);
        return fragment;
    CE_REACTIONS_METHOD_EXE
}


auto dom::node_ranges::range::clone_contents()
        -> nodes::document_fragment*
{
    CE_REACTIONS_METHOD_DEF
        // create a DocumentFragment node, and set its document to the same document that owns the 'start_container' of this
        // range; if this range is collapsed, then it doesn't contain anything, so return the empty DocumentFragment
        auto fragment = new nodes::document_fragment{};
        fragment->owner_document = start_container()->owner_document();
        return_if(collapsed()) fragment;

        // check if the start container of this Range is a textual container or not, ie is it / does it inherit the
        // CharacterData interface? (use the pointer as a boolean in if-statements)
        auto* textual_start_container = dynamic_cast<nodes::character_data*>(start_container());
        auto* textual_end_container   = dynamic_cast<nodes::character_data*>(end_container()  );

        // if the start container is textual, and the start and end containers are the same, then the Range is selecting a
        // textual node's contents, so clone the text from the 'start_offset' to the 'end_offset', append the extracted
        // text into 'fragment', and return 'fragment' - no more processing to do for single node contents extraction
        if (textual_start_container && textual_end_container && start_container() == end_container())
        {
            detail::copy_data(start_container(), fragment, textual_start_container, start_offset(), end_offset(), false);
            return fragment;
        }

        // get the 'first_partially_contained_child', 'last_partially_contained_child', 'contained_children', by calling the
        // helper method, which determines these values using range filters
        auto [first_partially_contained_child, last_partially_contained_child, contained_children] =
                detail::get_range_containment_children(this, start_container(), end_container());

        detail::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [contained_children] {return ranges::any_of(contained_children, ext::bind_front(detail::is_document_type_node));},
                "Contained children cannot be DocumentType nodes");

        textual_start_container && dynamic_cast<nodes::character_data*>(first_partially_contained_child)
                ? detail::copy_data(
                        first_partially_contained_child, fragment, textual_start_container, start_offset(),
                        detail::length(start_container()), true)

                : detail::append_to_sub_fragment(
                        first_partially_contained_child, fragment, start_container(), start_offset(),
                        first_partially_contained_child, detail::length(first_partially_contained_child),
                        detail::CLONE);

        for (auto* contained_child: contained_children)
            detail::append(contained_child->clone_node(true), fragment);

        textual_end_container && dynamic_cast<nodes::character_data*>(last_partially_contained_child)
                ? detail::copy_data(
                        last_partially_contained_child, fragment, textual_end_container, 0, end_offset(), true)

                : detail::append_to_sub_fragment(
                        last_partially_contained_child, fragment, last_partially_contained_child, 0, end_container(),
                        end_offset(), detail::CLONE);

        return fragment;
    CE_REACTIONS_METHOD_EXE
}


auto dom::node_ranges::range::delete_contents()
        -> nodes::document_fragment*
{
    CE_REACTIONS_METHOD_DEF
        return_if(collapsed()) static_cast<nodes::document_fragment*>(nullptr);

        // check if the start container of this Range is a textual container or not, ie is it / does it inherit the
        // CharacterData interface? (use the pointer as a boolean in if-statements)
        auto* textual_start_container = dynamic_cast<nodes::character_data*>(start_container());
        auto* textual_end_container   = dynamic_cast<nodes::character_data*>(end_container()  );

        // if the start container is textual, and the start and end containers are the same, then the Range is selecting a
        // textual node's contents, so clone the text from the 'start_offset' to the 'end_offset', append the extracted
        // text into 'fragment', and return 'fragment' - no more processing to do for single node contents extraction
        if (textual_start_container && textual_end_container && start_container() == end_container())
        {
            detail::replace_data(textual_start_container, start_offset(), end_offset() - start_offset(), "");
            return static_cast<nodes::document_fragment*>(nullptr); // TODO : return value
        }

        auto nodes_to_remove = detail::descendants(m_root)
                | ranges::views::filter([this](nodes::node* node) {return  detail::contains(node, this);})
                | ranges::views::filter([this](nodes::node* node) {return !detail::contains(node->parent_node(), this);});

        // get the 'new_node' and 'new_offset', by calling the helper method, which determines theses values using the
        // containers and the 'start_offset'
        auto [new_node, new_offset] =
                detail::create_new_node_and_offset(start_container(), end_container(), start_offset());

        if (textual_start_container)
            detail::replace_data(textual_start_container, start_offset(), detail::length(start_container()), "");

        for (const auto& node_to_remove: nodes_to_remove)
            detail::remove(node_to_remove);

        if (textual_end_container)
            detail::replace_data(textual_end_container, 0, end_offset(), "");

        ext::tie(start_container, start_offset) = ext::make_tuple(new_node, new_offset);
        ext::tie(end_container  , end_offset  ) = ext::make_tuple(new_node, new_offset);

        return static_cast<nodes::document_fragment*>(nullptr); // TODO : return value
    CE_REACTIONS_METHOD_EXE
}


auto dom::node_ranges::range::surround_contents(
        nodes::node* parent)
        -> nodes::document_fragment*
{
    CE_REACTIONS_METHOD_DEF
        detail::throw_v8_exception_formatted<INVALID_STATE_ERR>(
                [this] {return ranges::any_of(
                        detail::descendants(m_root) | ranges::views::filter(ext::bind_back(detail::partially_contains, this)),
                        [](nodes::node* node) {return !dynamic_cast<nodes::text*>(node);});},
                "Cannot surround a Range that partially contains non-Text nodes");

        detail::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
                [parent] {return ext::multi_cast<nodes::document*, nodes::document_type*, nodes::document_fragment*>(parent);},
                "New parent can not be a Document, DocumentType or DocumentFragment");

        auto* fragment = extract_contents();
        detail::replace_all(nullptr, parent);
        detail::append(parent, fragment);
        insert_node(parent);
        select_node(parent);

        return fragment;
    CE_REACTIONS_METHOD_EXE
}


auto dom::node_ranges::range::collapse(
        ext::boolean  to_start)
        -> void
{
    to_start
            ? ext::tie(end_container  , end_offset)   = ext::make_tuple(start_container(), start_offset())
            : ext::tie(start_container, start_offset) = ext::make_tuple(end_container()  , end_offset()  );
}


auto dom::node_ranges::range::clone_range()
        const -> range
{
    range new_range;
    ext::tie(new_range.start_container, new_range.start_offset) = ext::make_tuple(start_container(), start_offset());
    ext::tie(new_range.end_container  , new_range.end_offset  ) = ext::make_tuple(end_container()  , end_offset()  );
    return new_range;
}


auto dom::node_ranges::range::to_json()
        const -> ext::string
{
    ext::string s;
    auto* textual_start_container = dynamic_cast<nodes::character_data*>(start_container());
    auto* textual_end_container   = dynamic_cast<nodes::character_data*>(end_container()  );

    if (textual_start_container && textual_end_container && start_container() == end_container())
        return detail::substring_data(textual_start_container, start_offset(), end_offset() - start_offset());

    if (textual_start_container)
        s += detail::substring_data(textual_start_container, start_offset(), detail::length(textual_start_container) - start_offset());
    
    s += detail::descendant_text_nodes(m_root)
            | ranges::views::filter(ext::bind_back(detail::contains, this))
            | ranges::views::transform([](nodes::text* text_node) {return text_node->data();})
            | ranges::to<ext::string>();

    if (textual_end_container)
        s += detail::substring_data(textual_end_container, 0, end_offset());
}


auto dom::node_ranges::range::get_common_ancestor_container()
        const -> decltype(this->common_ancestor_container)::value_t
{
    return detail::common_ancestor(start_container(), end_container());
}


auto dom::node_ranges::range::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<range>{isolate}
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
            .function("toJSON", &range::to_json)
            .var("commonAncestorContainer", &range::common_ancestor_container, true)
            .auto_wrap_objects();
}
