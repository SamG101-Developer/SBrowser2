#include "range.hpp"
#include "range/v3/algorithm/any_of.hpp"
#include "range/v3/algorithm/for_each.hpp"
#include "range/v3/view/filter.hpp"
#include "range/v3/view/transform.hpp"

#include <memory>
#include <tuple>

#include <ext/boolean.hpp>
#include <ext/casting.hpp>
#include <ext/functional.hpp>
#include <ext/ranges.hpp>

#include <javascript/environment/realms_2.hpp>

#include <web_apis/dom/detail/customization_internals.hpp>
#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/mutation_internals.hpp>
#include <web_apis/dom/detail/range_internals.hpp>
#include <web_apis/dom/detail/text_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>

#include <web_apis/dom/nodes/character_data.hpp>
#include <web_apis/dom/nodes/comment.hpp>
#include <web_apis/dom/nodes/document.hpp>
#include <web_apis/dom/nodes/document_fragment.hpp>
#include <web_apis/dom/nodes/document_type.hpp>
#include <web_apis/dom/nodes/processing_instruction.hpp>
#include <web_apis/dom/nodes/text.hpp>

namespace dom::nodes {class window;}


dom::node_ranges::range::range()
{
    bind_get(common_ancestor_container);

    JS_REALM_GET_CURRENT
    start_container = javascript::environment::realms_2::get<nodes::document*>(current_global_object, "associated_document");
    end_container   = javascript::environment::realms_2::get<nodes::document*>(current_global_object, "associated_document");
    start_offset    = 0;
    end_offset      = 0;

    m_root = nullptr;
}


auto dom::node_ranges::range::set_start(
        nodes::node* new_container,
        ext::number_view<ulong> new_offset)
        -> void
{
    // set the start of this range to the 'new_container' and 'new_offset' variables, by calling the detail method with
    // the same variables
    detail::range_internals::set_start_or_end(this, new_container, new_offset, true);
}


auto dom::node_ranges::range::set_start_before(
        nodes::node* new_container)
        -> void
{
    // set the start of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::tree_internals::index(new_container);
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::node_ranges::range::set_start_after(
        nodes::node* new_container)
        -> void
{
    // set the start of this range to be after the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::tree_internals::index(new_container) + 1;
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, true);
}


auto dom::node_ranges::range::set_end(
        nodes::node* new_container,
        ext::number_view<ulong> new_offset)
        -> void
{
    // set the end of this range to the 'new_container' and 'new_offset' variables, by calling the detail method with
    // the same variables
    detail::range_internals::set_start_or_end(this, new_container, new_offset, false);
}


auto dom::node_ranges::range::set_end_before(
        nodes::node* new_container)
        -> void
{
    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::tree_internals::index(new_container);
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::node_ranges::range::set_end_after(
        nodes::node* new_container)
        -> void
{
    // set the end of this range to be before the 'new_container', by calling the detail method with the parent of the
    // 'new_container' and the index of the 'new_container' + 1 as the offset
    verify_parent_exists(new_container);
    auto parent_node = new_container->parent_node();
    auto new_offset = detail::tree_internals::index(new_container) + 1;
    detail::range_internals::set_start_or_end(this, parent_node, new_offset, false);
}


auto dom::node_ranges::range::insert_node(
        nodes::node* new_container)
        -> nodes::node*
{
    ce_reactions_method_def
        detail::exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [this, new_container]{return ext::multi_cast<nodes::comment*, nodes::processing_instruction*>(start_container())
                        || dynamic_cast<nodes::text*>(start_container()) && !new_container->parent_node()
                        || start_container() == new_container;},
                "Cannot insert a new container into a Range whose start node is a Comment/ProcessingInstruction, an orphaned Text node, or is the new container");

        // the 'reference_node' is the node that the 'new_container' will be inserted before; if the start container is a
        // Text node, then set the 'reference_node' to the start container (insert before all the text), otherwise the
        // child of the non-Text start container whose index is the offset (exact correct node)
        auto* reference_node = dynamic_cast<nodes::text*>(start_container())
                ? start_container()
                : ranges::first_where(*start_container->child_nodes(), [this](nodes::node* child_node) {return detail::tree_internals::index(child_node) == start_offset();});

        // the 'parent_node' is the parent that the 'new_container' is going to be inserted into; if there is no
        // 'reference_node', then the parent is the start container, otherwise it's the reference node's parent node (the
        // 'new_container' will be inserted before the 'reference_node' into the 'parent_node'
        auto* parent_node = !reference_node
                ? start_container()
                : reference_node->parent_node();

        // if the reference node is a Text node, set it to everything after the start offset, otherwise if the reference
        // node is the 'new_container', then set it to the next sibling, otherwise leave it as it is
        reference_node = dynamic_cast<nodes::text*>(start_container())
                ? detail::text_internals::split(dynamic_cast<nodes::text*>(start_container()), start_offset())
                : new_container == reference_node ? reference_node->next_sibling() : reference_node;

        // the 'new_offset' is the length of the 'parent_node' if there is no 'reference_node', otherwise it's the index of
        // the 'reference_node'. adjust the 'new_offset' by the length of the 'new_container' if it's a DocumentFragment,
        // otherwise 1 (number of children being inserted)
        auto new_offset = !reference_node ? detail::tree_internals::length(parent_node) : detail::tree_internals::index(reference_node);
        new_offset += dynamic_cast<nodes::document_fragment*>(new_container) ? detail::tree_internals::length(new_container) : 1;

        // ensure that the 'new_container' can be inserted into the 'parent_node' before the 'reference_node', remove the
        // 'new_container' from its current parent (if it has a parent), and insert it into the 'parent_node' before the
        // 'reference_node'
        detail::mutation_internals::ensure_pre_insertion_validity(new_container, parent_node, reference_node);
        detail::mutation_internals::remove(new_container->parent_node() ? new_container : nullptr);
        detail::mutation_internals::pre_insert(new_container, parent_node, reference_node);

        // if the range is currently collapsed, then set the end container and offset to the 'parent_node' and the
        // 'new_offset', so that the range maintains its collapsed state
        if (collapsed())
            std::tie(end_container, end_offset) = std::tuple(parent_node, new_offset);

        return new_container;

    ce_reactions_method_exe
}


auto dom::node_ranges::range::intersects_node(
        nodes::node* container)
        const -> ext::boolean
{
    // return false if the range's root doesn't match the node's root, and return true if teh node doesn't have a parent
    // (orphaned nodes are always intercepted by all ranges)
    return_if(detail::tree_internals::root(container) != m_root) false;
    return_if(!container->parent_node()) true;

    // get the container's parent and offset, as they would be called multiple times otherwise, and save them under
    // variables
    auto container_parent = container->parent_node();
    auto container_offset = detail::tree_internals::index(container);

    // if the node occurs before the end of the range, and after the start of the range, then it must be within the
    // range, and therefor is intersected by the range
    auto is_before_end  = detail::range_internals::position_relative(container_parent, container_offset + 0, end_container()  , end_offset()  ) == detail::range_internals::BEFORE;
    auto is_after_start = detail::range_internals::position_relative(container_parent, container_offset + 1, start_container(), start_offset()) == detail::range_internals::AFTER;
    return is_before_end && is_after_start;
}


auto dom::node_ranges::range::select_node(
        nodes::node* container)
        -> void
{
    verify_parent_exists(container);

    // get the index if the container sand save it as a variable to remove code duplication
    auto index = detail::tree_internals::index(container);

    // set the start and end containers to the parent of the container (so that the container is contained by the
    // range), and set the start offset to the index of the container (so the first node is the container), and set the
    // end offset to the index of the container + 1 (so the only node in the range is the container)
    auto parent_node = container->parent_node();
    std::tie(start_container, start_offset) = std::make_tuple(parent_node, index);
    std::tie(end_container, end_offset) = std::make_tuple(parent_node, index + 1);
}


auto dom::node_ranges::range::select_node_contents(
        nodes::node* container)
        -> void
{
    // if the container is a DocumentType node, then throw an invalid node error
    detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<nodes::document_type*>(container);},
            "Container can not be a DocumentType node");

    // set the start container to the 'container', and the start offset to 0; set the end container to the container,
    // and the offset to the length of the container this will mean that the range only contains the entire contents of
    // the range
    auto l = detail::tree_internals::length(container);
    std::tie(start_container, start_offset) = std::make_tuple(container, 0);
    std::tie(end_container, end_offset)     = std::make_tuple(container, l);
}


auto dom::node_ranges::range::compare_boundary_points(
        ext::number_view<ushort> how,
        dom::node_ranges::range* source_range)
        -> ext::number<short>
{
    // if the root of the 'source_range' doesn't this Range's root, then throw a wrong document error, because it isn't
    // possible to compare boundary points or ranges that are in different documents
    detail::exception_internals::throw_v8_exception_formatted<WRONG_DOCUMENT_ERR>(
            [this, source_range] {return m_root != source_range->m_root;},
            "sourceRange's root must equal this Range's root");

    // set 'this_container/_offset' and 'that_container/_offset' to nullptr/0, to prepare them for the switch-case
    // block that determines their values based on the 'how' parameter
    auto [this_container, this_offset] = std::make_tuple(static_cast<nodes::node*>(nullptr), 0);
    auto [that_container, that_offset] = std::make_tuple(static_cast<nodes::node*>(nullptr), 0);

    // there are 4 different ways to compare the boundary points of 2 Range objects - the start and end of either Range
    // can be compared against the start or end of the other range, giving 4 different possibilities of comparison
    // methods
    number_switch(how)
    {
        number_case(START_TO_START): // start of that range to start of this range
            std::tie(this_container, this_offset) = std::make_tuple(start_container(), start_offset());
            std::tie(that_container, that_offset) = std::make_tuple(source_range->start_container(), source_range->start_offset());
            break;

        number_case(START_TO_END): // start of that range to end of this range
            std::tie(this_container, this_offset) = std::make_tuple(end_container(), end_offset());
            std::tie(that_container, that_offset) = std::make_tuple(source_range->start_container(), source_range->start_offset());
            break;

        number_case(END_TO_END): // end of that range to end of this range
            std::tie(this_container, this_offset) = std::make_tuple(end_container(), end_offset());
            std::tie(that_container, that_offset) = std::make_tuple(source_range->end_container(), source_range->end_offset());
            break;

        number_case(END_TO_START): // end of that range to start of this range
            std::tie(this_container, this_offset) = std::make_tuple(start_container(), start_offset());
            std::tie(that_container, that_offset) = std::make_tuple(source_range->end_container(), source_range->end_offset());
            break;

        number_default: // if the 'how' value is invalid, throw a not supported error
            detail::exception_internals::throw_v8_exception_formatted<NOT_SUPPORTED_ERR>(NO_CONDITION, "The 'how' parameter must be 0 <= how <= 3");
            break;
    }

    // determine the position of 'this_container/_offset' compared to 'that_container/_offset' using the detail
    // comparison method
    return (short) detail::range_internals::position_relative(this_container, this_offset, that_container, that_offset);
}


auto dom::node_ranges::range::compare_point(
        nodes::node* container,
        ext::number_view<ulong> offset)
        const -> ext::number<short>
{
    detail::exception_internals::throw_v8_exception_formatted<WRONG_DOCUMENT_ERR>(
            [this, container_root = detail::tree_internals::root(container)] {return m_root != container_root;},
            "Container's root must equal this Range's root");

    detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<nodes::document_type*>(container);},
            "Container can not be a DocumentType node");

    detail::exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [offset, length = std::move(detail::tree_internals::length(container))] {return offset > length;},
            "Offset must be <= length of the node");

    return_if(detail::range_internals::position_relative(container, offset, start_container(), start_offset()) == detail::range_internals::BEFORE) -1;
    return_if(detail::range_internals::position_relative(container, offset, end_container(), end_offset()) == detail::range_internals::AFTER) 1;
    return 0;
}


auto dom::node_ranges::range::is_point_in_range(
        nodes::node* container,
        ext::number_view<ulong> offset)
        const -> ext::boolean
{
    return_if(m_root != detail::tree_internals::root(container)) false;

    detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
            [container] {return !ext::multi_cast<nodes::document_type*>(container);},
            "Container can not be a DocumentType node");

    detail::exception_internals::throw_v8_exception_formatted<INDEX_SIZE_ERR>(
            [offset, length = std::move(detail::tree_internals::length(container))] {return offset > length;},
            "Offset must be <= length of the node");

    auto is_before_end  = detail::range_internals::position_relative(container, offset, end_container()  , end_offset()  ) == detail::range_internals::BEFORE;
    auto is_after_start = detail::range_internals::position_relative(container, offset, start_container(), start_offset()) == detail::range_internals::AFTER;
    return is_before_end && is_after_start;
}


auto dom::node_ranges::range::extract_contents()
        -> nodes::document_fragment*
{
    ce_reactions_method_def
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
            detail::range_internals::copy_data(start_container(), fragment, textual_start_container, start_offset(), end_offset(), true);
            return fragment;
        }

        // get the 'first_partially_contained_child', 'last_partially_contained_child', 'contained_children', by calling the
        // helper method, which determines these values using range filters
        auto [first_partially_contained_child, last_partially_contained_child, contained_children] =
                detail::range_internals::get_range_containment_children(this, start_container(), end_container());

        // get the 'new_node' and 'new_offset', by calling the helper method, which determines theses values using the
        // containers and the 'start_offset'
        auto [new_node, new_offset] =
                detail::range_internals::create_new_node_and_offset(start_container(), end_container(), start_offset());

        detail::exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [contained_children] {return ranges::any_of(contained_children, ext::bind_front(detail::tree_internals::is_document_type_node));},
                "Contained children cannot be DocumentType nodes");

        textual_start_container && dynamic_cast<nodes::character_data*>(first_partially_contained_child)
                ? detail::range_internals::copy_data(
                        first_partially_contained_child, fragment, textual_start_container, start_offset(),
                        detail::tree_internals::length(start_container()), true)

                : detail::range_internals::append_to_sub_fragment(
                        first_partially_contained_child, fragment, start_container(), start_offset(),
                        first_partially_contained_child, detail::tree_internals::length(first_partially_contained_child),
                        detail::range_internals::EXTRACT);

        for (auto* contained_child: contained_children)
            detail::mutation_internals::append(contained_child, fragment);

        textual_end_container && dynamic_cast<nodes::character_data*>(last_partially_contained_child)
                ? detail::range_internals::copy_data(
                        last_partially_contained_child, fragment, textual_end_container, 0, end_offset(), true)

                : detail::range_internals::append_to_sub_fragment(
                        last_partially_contained_child, fragment, last_partially_contained_child, 0, end_container(),
                        end_offset(), detail::range_internals::EXTRACT);

        std::tie(start_container, start_offset) = std::make_tuple(new_node, new_offset);
        std::tie(end_container  , end_offset  ) = std::make_tuple(new_node, new_offset);
        return fragment;
    ce_reactions_method_exe
}


auto dom::node_ranges::range::clone_contents()
        -> nodes::document_fragment*
{
    ce_reactions_method_def
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
            detail::range_internals::copy_data(start_container(), fragment, textual_start_container, start_offset(), end_offset(), false);
            return fragment;
        }

        // get the 'first_partially_contained_child', 'last_partially_contained_child', 'contained_children', by calling the
        // helper method, which determines these values using range filters
        auto [first_partially_contained_child, last_partially_contained_child, contained_children] =
                detail::range_internals::get_range_containment_children(this, start_container(), end_container());

        detail::exception_internals::throw_v8_exception_formatted<HIERARCHY_REQUEST_ERR>(
                [contained_children] {return ranges::any_of(contained_children, ext::bind_front(detail::tree_internals::is_document_type_node));},
                "Contained children cannot be DocumentType nodes");

        textual_start_container && dynamic_cast<nodes::character_data*>(first_partially_contained_child)
                ? detail::range_internals::copy_data(
                        first_partially_contained_child, fragment, textual_start_container, start_offset(),
                        detail::tree_internals::length(start_container()), true)

                : detail::range_internals::append_to_sub_fragment(
                        first_partially_contained_child, fragment, start_container(), start_offset(),
                        first_partially_contained_child, detail::tree_internals::length(first_partially_contained_child),
                        detail::range_internals::CLONE);

        for (auto* contained_child: contained_children)
            detail::mutation_internals::append(contained_child->clone_node(true), fragment);

        textual_end_container && dynamic_cast<nodes::character_data*>(last_partially_contained_child)
                ? detail::range_internals::copy_data(
                        last_partially_contained_child, fragment, textual_end_container, 0, end_offset(), true)

                : detail::range_internals::append_to_sub_fragment(
                        last_partially_contained_child, fragment, last_partially_contained_child, 0, end_container(),
                        end_offset(), detail::range_internals::CLONE);

        return fragment;
    ce_reactions_method_exe
}


auto dom::node_ranges::range::delete_contents()
        -> nodes::document_fragment*
{
    ce_reactions_method_def
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
            detail::text_internals::replace_data(textual_start_container, start_offset(), end_offset() - start_offset(), "");
            return static_cast<nodes::document_fragment*>(nullptr); // TODO : return value
        }

        auto nodes_to_remove = detail::tree_internals::descendants(m_root)
                | ranges::views::filter([this](nodes::node* node) {return  detail::range_internals::contains(node, this);})
                | ranges::views::filter([this](nodes::node* node) {return !detail::range_internals::contains(node->parent_node(), this);});

        // get the 'new_node' and 'new_offset', by calling the helper method, which determines theses values using the
        // containers and the 'start_offset'
        auto [new_node, new_offset] =
                detail::range_internals::create_new_node_and_offset(start_container(), end_container(), start_offset());

        if (textual_start_container)
            detail::text_internals::replace_data(textual_start_container, start_offset(), detail::tree_internals::length(start_container()), "");

        for (const auto& node_to_remove: nodes_to_remove)
            detail::mutation_internals::remove(node_to_remove);

        if (textual_end_container)
            detail::text_internals::replace_data(textual_end_container, 0, end_offset(), "");

        std::tie(start_container, start_offset) = std::make_tuple(new_node, new_offset);
        std::tie(end_container  , end_offset  ) = std::make_tuple(new_node, new_offset);

        return static_cast<nodes::document_fragment*>(nullptr); // TODO : return value
    ce_reactions_method_exe
}


auto dom::node_ranges::range::surround_contents(
        nodes::node* parent)
        -> nodes::document_fragment*
{
    ce_reactions_method_def
        detail::exception_internals::throw_v8_exception_formatted<INVALID_STATE_ERR>(
                [this] {return ranges::any_of(
                        detail::tree_internals::descendants(m_root) | ranges::views::filter(ext::bind_back(detail::range_internals::partially_contains, this)),
                        [](nodes::node* node) {return !dynamic_cast<nodes::text*>(node);});},
                "Cannot surround a Range that partially contains non-Text nodes");

        detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>(
                [parent] {return ext::multi_cast<nodes::document*, nodes::document_type*, nodes::document_fragment*>(parent);},
                "New parent can not be a Document, DocumentType or DocumentFragment");

        auto* fragment = extract_contents();
        detail::mutation_internals::replace_all(nullptr, parent);
        detail::mutation_internals::append(parent, fragment);
        insert_node(parent);
        select_node(parent);

        return fragment;
    ce_reactions_method_exe
}


auto dom::node_ranges::range::collapse(
        ext::boolean_view to_start)
        -> void
{
    to_start
            ? std::tie(end_container  , end_offset)   = std::make_tuple(start_container(), start_offset())
            : std::tie(start_container, start_offset) = std::make_tuple(end_container()  , end_offset()  );
}


auto dom::node_ranges::range::clone_range()
        const -> range
{
    range new_range;
    std::tie(new_range.start_container, new_range.start_offset) = std::make_tuple(start_container(), start_offset());
    std::tie(new_range.end_container  , new_range.end_offset  ) = std::make_tuple(end_container()  , end_offset()  );
    return new_range;
}


auto dom::node_ranges::range::to_json()
        const -> ext::string
{
    ext::string s;
    auto* textual_start_container = dynamic_cast<nodes::character_data*>(start_container());
    auto* textual_end_container   = dynamic_cast<nodes::character_data*>(end_container()  );

    if (textual_start_container && textual_end_container && start_container() == end_container())
        return detail::text_internals::substring_data(textual_start_container, start_offset(), end_offset() - start_offset());

    if (textual_start_container)
        s += detail::text_internals::substring_data(textual_start_container, start_offset(), detail::tree_internals::length(textual_start_container) - start_offset());
    
    s += detail::tree_internals::descendant_text_nodes(m_root)
            | ranges::views::filter(ext::bind_back(detail::range_internals::contains, this))
            | ranges::views::transform([](nodes::text* text_node) {return text_node->data();})
            | ranges::to<ext::string>();

    if (textual_end_container)
        s += detail::text_internals::substring_data(textual_end_container, 0, end_offset());
}


auto dom::node_ranges::range::get_common_ancestor_container()
        const -> nodes::node*
{
    return detail::tree_internals::common_ancestor(start_container(), end_container());
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
