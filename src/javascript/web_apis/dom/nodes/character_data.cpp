#include "character_data.hpp"

#include <web_apis/dom/detail/text_internals.hpp>
#include <web_apis/dom/detail/tree_internals.hpp>


dom::nodes::character_data::character_data()
{
    bind_get(length);
}


auto dom::nodes::character_data::substring_data(
        ext::number_view<ulong> offset,
        ext::number_view<ulong> count)
        const -> ext::string
{
    // substring the data: substring 'count' characters from the index 'offset'
    return detail::text_internals::substring_data(this, offset, count);
}


auto dom::nodes::character_data::append_data(
        ext::string_view new_data)
        -> void
{
    // append data: replace 0 characters after the length of this node with the 'new_data'
    return detail::text_internals::replace_data(this, detail::tree_internals::length(this), 0, new_data);
}


auto dom::nodes::character_data::insert_data(
        ext::number_view<ulong> offset,
        ext::string_view new_data)
        -> void
{
    // insert data: replace 0 characters after 'offset' with 'new_data'
    return detail::text_internals::replace_data(this, offset, 0, new_data);
}


auto dom::nodes::character_data::delete_data(
        ext::number_view<ulong> offset,
        ext::number_view<ulong> count)
        -> void
{
    // delete data: replace 'count' characters after 'offset' with nothing
    return detail::text_internals::replace_data(this, offset, count, "");
}


auto dom::nodes::character_data::replace_data(
        ext::number_view<ulong> offset,
        ext::number_view<ulong> count,
        ext::string_view new_data)
        -> void
{
    // replace data: replace 'count' characters after 'offset' with 'new_data'
    return detail::text_internals::replace_data(this, offset, count, new_data);
}


auto dom::nodes::character_data::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<character_data>{isolate}
            .inherit<node>()
            .inherit<dom::mixins::child_node>()
            .inherit<dom::mixins::non_document_type_child_node>()

            .function("substringData", &character_data::substring_data)
            .function("appendData", &character_data::append_data)
            .function("insertData", &character_data::insert_data)
            .function("replaceData", &character_data::replace_data)
            .function("deleteData", &character_data::delete_data)

            .var("data", &character_data::data, false)
            .var("length", &character_data::length, true)
            .auto_wrap_objects();
}

