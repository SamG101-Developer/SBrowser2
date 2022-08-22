#include "console.hpp"

#include <ostream>

#include "_typedefs.hpp"
#include "ext/functional.hpp"
#include "ext/ranges.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"

#include "console/detail/abstract_operations.hpp"

#include <fmt/ostream.h>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/max_element.hpp>
#include <v8-debug.h>
#include <v8pp/convert.hpp>


template <typename ...Args>
auto console::console::assert_(
        ext::boolean&& condition,
        Args&& ...data) -> void
{
    return_if (condition);

    ext::string message = "Assertion failed";
    auto data_tuple = sizeof...(data) == 0
            ? ext::forward_as_tuple(std::move(message))
            : ext::forward_as_tuple(std::forward<Args>(data)...);

    if (std::tuple_size(data_tuple) > 0)
    {
        auto first = ext::get<0>(data_tuple);
        if constexpr (type_is<decltype(first), ext::string>)
            data_tuple = ext::tuple_cat(data_tuple, ext::forward_as_tuple(std::move(message)));
        else
            std::get<0>(data_tuple) = std::move(message) + char(0x003a) + char(0x0020) + first.template to<ext::string>();
    }

    ext::apply(
            ext::bind_front{detail::logger, detail::log_level_t::ASSERT_},
            std::move(data_tuple));
}


auto console::console::clear()
        -> void
{
    m_group_stack = {};
}


template <typename ...Args>
auto console::console::debug(
        Args&& ...data)
        -> void
{
    detail::logger(detail::log_level_t::DEBUG, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::error(
        Args&& ...data)
        -> void
{
    detail::logger(detail::log_level_t::ERROR, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::info(
        Args&& ...data)
        -> void
{
    detail::logger(detail::log_level_t::INFO, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::log(
        Args&& ...data)
        -> void
{
    detail::logger(detail::log_level_t::LOG, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::warn(
        Args&& ...data)
        -> void
{
    detail::logger(detail::log_level_t::WARN, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::table(
        ext::vector<ext::tuple<Args...>>&& table_data,
        ext::vector<ext::string>&& properties) -> void
{
    // get the number of columns, by getting the size of the arguments (allows for un-named properties). add empty
    // property names if the number of columns is greater than the number of properties given
    ext::number number_columns = sizeof...(Args);
    for_if (number_columns > properties.size(), auto i = properties.size(); i < number_columns; ++i)
        properties.template emplace_back("");

    // prepend the property row into the table data by converting the vector into a tuple, and emplacing it at the front
    // of the 'table_data'. create an array to hol the maximum length of each column in the table
    table_data.template emplace_front(ext::make_tuple(std::move(properties)));

    // iterate through each column in the table, to determine the maximum cell length for each column
    auto length_of_object = []<typename T>(T&& object) {return strlen(fmt::formatter<T>::format(object).size());};
    auto pad_string = [](ext::string& string, ext::number<ext::string::size_type> pad) {string.insert(string.begin(), pad, ' ');};
    auto max_lengths = table_data
            | ranges::views::transpose()
            | ranges::views::transform([](auto& column) {return column | ranges::views::transform(length_of_object);})
            | ranges::views::transform(ranges::max_element);

    // pad each cell to the correct length, join the cells with a pipe, and join the rows with newlines
    auto formatted = table_data
            | ranges::views::transpose()
            | ranges::views::transform([]<template <typename> typename C, typename U>(C<U>& column) {return column
                    | ranges::views::transform(fmt::formatter<U>::format)
                    | ranges::views::transform(ext::bind_back(pad_string, max_lengths | ranges::views::take(0)));}) // TODO : remove 0th element from max_lengths
            | ranges::views::transpose()
            | ranges::views::transform([](auto& row) {return row | ranges::views::join('|');})
            | ranges::views::join('\n');

    // log this table row by row
    ext::apply(
            [](auto&& table_rows) {detail::logger(detail::log_level_t::LOG, std::move(table_rows));},
            ext::make_tuple(std::move(formatted)));

}


template <typename ...Args>
auto console::console::trace(
        Args&& ...data)
        -> void
{
    auto* isolate = v8::Isolate::GetCurrent();
    auto trace = v8pp::from_v8<ext::vector<ext::string>>(isolate, v8::StackTrace::CurrentStackTrace(isolate, 10));
    auto formatted_data = detail::formatter(std::forward<Args>(data)...);
    trace.template emplace_front(formatted_data);
    ext::apply(ext::bind_front{detail::printer, detail::print_type_t::TRACE}, ext::make_tuple(std::move(trace)));
}
