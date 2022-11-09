#include "character_data.hpp"
#include "character_data_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"


dom::nodes::character_data::character_data()
{
    INIT_PIMPL(character_data);
}


auto dom::nodes::character_data::substring_data(ext::number<ulong> offset, ext::number<ulong> count) const -> ext::string
{
    // To substring the data, substring 'count' characters from the index 'offset' (from the 'data' attribute stored in
    // the private class). Return the result of substringing the data (the private-class'data' attribute remains the
    // same hence the const-function-qualifier, so don't change and return it).
    return detail::substring_data(this, offset, count);
}


auto dom::nodes::character_data::append_data(ext::string&& new_data) -> ext::string
{
    // To append data: replace 0 characters after the length of this node with the 'new_data' (from the 'data' attribute
    // stored in the private class). This is semantically the same as appending data, but uses a common detail procedure
    // to multiple other class methods to reduce code duplication. Return the 'data'.
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, detail::length(this), 0, std::move(new_data));
    return d->data;
}


auto dom::nodes::character_data::insert_data(
        ext::number<ulong> offset,
        ext::string&& new_data)
        -> ext::string
{
    // To insert data: replace 0 characters after 'offset' with 'new_data' (from the 'data' attribute stored in the
    // private class). This is semantically the same as inserting data, but uses a common detail procedure to multiple
    // other class methods to reduce code duplication. Return the 'data'.
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, offset, 0, std::move(new_data));
    return d->data;
}


auto dom::nodes::character_data::delete_data(
        ext::number<ulong> offset,
        ext::number<ulong> count)
        -> ext::string
{
    // To delete data: replace 'count' characters after 'offset' with nothing (from the 'data' attribute stored in the
    // private class). This is semantically the same as deleting data, but uses a common detail procedure to multiple
    // other class methods to reduce code duplication. Return the 'data'.
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, offset, count, u"");
    return d->data;
}


auto dom::nodes::character_data::replace_data(
        ext::number<ulong> offset,
        ext::number<ulong> count,
        ext::string&& new_data)
        -> ext::string
{
    // To replace data: replace 'count' characters after 'offset' with 'new_data' (from the 'data' attribute stored in
    // the private class). This is semantically the same as replacing data, but uses a common detail procedure to
    // multiple other class methods to reduce code duplication. Return the 'data'.
    ACCESS_PIMPL(character_data);
    detail::replace_data(this, offset, count, std::move(new_data));
    return d->data;
}


auto dom::nodes::character_data::get_node_value() const -> ext::string
{
    // The 'node_value' getter returns the equivalent 'data' attribute value that is stored in the private class. Apply
    // custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const character_data);
        return d->data;
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::get_text_content() const -> ext::string
{
    // The 'text_content' getter returns the equivalent 'data' attribute value that is stored in the private class.
    // Apply custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const character_data);
        return d->data;
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::set_node_value(ext::string new_node_value) -> ext::string
{
    // The 'node_value' setter sets the equivalent 'data' attribute value that is stored in the private class to the
    // result of applying the 'replace_data(...)' method with the 'new_node_value', to handle bounds checks and live
    // Range updates. Apply custom element reactions to this setter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(character_data);
        return replace_data(0, d->data.length(), std::move(new_node_value));
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::set_text_content(ext::string new_text_content) -> ext::string
{
    // The 'text_content' setter sets the equivalent 'data' attribute value that is stored in the private class to the
    // result of applying the 'replace_data(...)' method with the 'new_node_value', to handle bounds checks and live
    // Range updates. Apply custom element reactions to this setter.
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(character_data);
        return replace_data(0, d->data.length(), std::move(new_text_content));
    CE_REACTIONS_METHOD_EXE;
}


auto dom::nodes::character_data::get_data() const -> ext::string
{
    // The 'data' getter returns the equivalent 'data' attribute value that is stored in the private class. Apply custom
    // element reactions to this getter.
    ACCESS_PIMPL(const character_data);
    return d->data;
}


auto dom::nodes::character_data::get_length() const -> ext::number<ulong>
{
    // The 'length' getter returns the length of the 'data' attribute value that is stored in the private class. Apply
    // custom element reactions to this getter.
    ACCESS_PIMPL(const character_data);
    return d->data.length();
}


auto dom::nodes::character_data::set_data(ext::string new_data) -> ext::string
{
    // The 'data' setter sets the equivalent 'data' attribute value that is stored in the private class to the result
    // of applying the 'replace_data(...)' method with the 'new_data', to handle bounds checks and live Range updates.
    // Apply custom element reactions to this setter.
    ACCESS_PIMPL(character_data);
    return replace_data(0, d->data.length(), std::move(new_data));
}


auto dom::nodes::character_data::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
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

