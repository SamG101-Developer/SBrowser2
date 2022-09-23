#include "character_data.hpp"

#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"


dom::nodes::character_data::character_data()
{
    bind_get(length);
}


auto dom::nodes::character_data::substring_data(
        ext::number<ulong> offset,
        ext::number<ulong> count)
        const -> ext::string
{
    // substring the data: substring 'count' characters from the index 'offset'
    return detail::substring_data(this, offset, count);
}


auto dom::nodes::character_data::append_data(
        ext::string&& new_data)
        -> ext::string
{
    // append data: replace 0 characters after the length of this node with the 'new_data'
    detail::replace_data(this, detail::length(this), 0, std::move(new_data));
    return d_ptr->data;
}


auto dom::nodes::character_data::insert_data(
        ext::number<ulong> offset,
        ext::string&& new_data)
        -> ext::string
{
    // insert data: replace 0 characters after 'offset' with 'new_data'
    detail::replace_data(this, offset, 0, std::move(new_data));
    return d_ptr->data;
}


auto dom::nodes::character_data::delete_data(
        ext::number<ulong> offset,
        ext::number<ulong> count)
        -> ext::string
{
    // delete data: replace 'count' characters after 'offset' with nothing
    detail::replace_data(this, offset, count, "");
    return d_ptr->data;
}


auto dom::nodes::character_data::replace_data(
        ext::number<ulong> offset,
        ext::number<ulong> count,
        ext::string&& new_data)
        -> ext::string
{
    // replace data: replace 'count' characters after 'offset' with 'new_data'
    detail::replace_data(this, offset, count, std::move(new_data));
    return d_ptr->data;
}


auto dom::nodes::character_data::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<character_data>{isolate}
        .inherit<node>()
        .inherit<dom::mixins::child_node>()
        .inherit<dom::mixins::non_document_type_child_node>()
        .function("substringData", &character_data::substring_data)
        .function("appendData", &character_data::append_data)
        .function("insertData", &character_data::insert_data)
        .function("replaceData", &character_data::replace_data)
        .function("deleteData", &character_data::delete_data)
        .property("data", &character_data::get_data, &character_data::set_data)
        .property("length", &character_data::get_length)
        .auto_wrap_objects();

    return std::move(conversion);
}

