#include "character_data.hpp"
#include "character_data_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"


dom::nodes::character_data::character_data()
{
    INIT_PIMPL(character_data);
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
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, detail::length(this), 0, std::move(new_data));
    return d->data;
}


auto dom::nodes::character_data::insert_data(
        ext::number<ulong> offset,
        ext::string&& new_data)
        -> ext::string
{
    // insert data: replace 0 characters after 'offset' with 'new_data'
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, offset, 0, std::move(new_data));
    return d->data;
}


auto dom::nodes::character_data::delete_data(
        ext::number<ulong> offset,
        ext::number<ulong> count)
        -> ext::string
{
    // delete data: replace 'count' characters after 'offset' with nothing
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, offset, count, "");
    return d->data;
}


auto dom::nodes::character_data::replace_data(
        ext::number<ulong> offset,
        ext::number<ulong> count,
        ext::string&& new_data)
        -> ext::string
{
    // replace data: replace 'count' characters after 'offset' with 'new_data'
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, offset, count, std::move(new_data));
    return d->data;
}


auto dom::nodes::character_data::get_node_value() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const character_data);
        return d->data;
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::get_text_content() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const character_data);
        return d->data;
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::set_node_value(ext::string new_node_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(character_data);
        replace_data(0, d->data.length(), std::move(new_node_value));
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::set_text_content(ext::string new_text_content) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(character_data);
        replace_data(0, d->data.length(), std::move(new_text_content));
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::get_data() const -> ext::string
{
    ACCESS_PIMPL(const character_data);
    return d->data;
}


auto dom::nodes::character_data::get_length() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const character_data);
    return d->data.length();
}


auto dom::nodes::character_data::set_data(ext::string new_data) -> ext::string
{
    ACCESS_PIMPL(character_data);
    d->data = std::move(new_data);
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

