#include "console.hpp"
#include "console_private.hpp"

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/hashing.hpp"
#include "ext/ranges.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/type_traits.hpp"

#include "javascript/environment/realms.hpp"

#include "console/detail/abstract_operations.hpp"
#include "hr_time/detail/time_internals.hpp"

#include <ostream>

#include <fmt/ostream.h>
#include <range/v3/action/remove.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/max_element.hpp>
#include <v8-debug.h>
#include <v8pp/convert.hpp>


template <typename ...Args>
auto console::console::assert_(ext::boolean condition, Args&& ...data) -> void
{
    // If the condition is true, then the assertion check has passed, and no information needs to be outputted, so
    // return early from the method
    return_if (condition);

    // Create a message, and if there were no arguments passed in as extra 'data', set the data tuple to the message,
    // otherwise forward the 'data' arguments into a tuple.
    auto message = u8"Assertion failed";
    auto data_tuple = sizeof...(data) == 0
            ? ext::forward_as_tuple(std::move(message))
            : ext::forward_as_tuple(std::forward<Args>(data)...);

    // If the original 'data' parameter pack contained any items, then perform some extra logic: if the first item in'
    // the tuple is not a string, prepend the 'message' to the tuple, so the first element is a message, otherwise set
    // the prepend the message to the first item with some formatting.
    if constexpr (sizeof...(data) > 0)
    {
        auto first = ext::get<0>(data_tuple);
        if constexpr (!ext::type_is<decltype(first), ext::string>)
            data_tuple = ext::tuple_cat(ext::forward_as_tuple(std::move(message)), data_tuple);
        else
            ext::get<0>(data_tuple) = std::move(message) + char(0x003a) + char(0x0020) + first.template to<ext::string>();
    }

    // Apply the 'data_tuple' to the 'detail::logger(...)' method, with the log level set to ASSERT.
    ext::apply(
            BIND_FRONT(detail::logger, detail::log_level_t::ASSERT_),
            std::move(data_tuple));
}


auto console::console::clear() -> void
{
    ACCESS_PIMPL(console);

    // Clear the associated group stack (in the GUI, this will remove all the outputted lines on the graphical console,
    // like 'cls' in the command prompt.
    d->group_stack.clear();
}


template <typename ...Args>
auto console::console::debug(Args&& ...data) -> void
{
    detail::logger(detail::log_level_t::DEBUG, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::error(Args&& ...data) -> void
{
    detail::logger(detail::log_level_t::ERROR, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::info(Args&& ...data) -> void
{
    detail::logger(detail::log_level_t::INFO, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::log(Args&& ...data) -> void
{
    detail::logger(detail::log_level_t::LOG, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::warn(Args&& ...data) -> void
{
    detail::logger(detail::log_level_t::WARN, std::forward<Args>(data)...);
}


template <typename ...Args>
auto console::console::table(
        ext::vector<ext::tuple<Args...>>&& table_data,
        ext::vector<ext::string>&& properties)
        -> void
{
    // Get the number of columns, by getting the size of the arguments (allows for un-named properties). Add empty
    // property names if the number of columns is greater than the number of properties given.
    ext::number number_columns = sizeof...(Args);
    for_if (number_columns > properties.size(), auto i = properties.size(); i < number_columns; ++i)
        properties.template emplace_back("");

    // Prepend the property row into the table data by converting the vector into a tuple, and emplacing it at the front
    // of the 'table_data'. Create an array to hol the maximum length of each column in the table.
    table_data.template emplace_front(ext::make_tuple(std::move(properties)));

    // Iterate through each column in the table, to determine the maximum cell length for each column.
    auto length_of_object = []<typename T>(T&& object) {return strlen(fmt::formatter<T>::format(object).size());};
    auto pad_string = [](ext::string& string, ext::number<ext::string::size_type> pad) {string.insert(string.begin(), *pad, ' ');};
    auto max_lengths = table_data
            | ranges::views::transpose
            | ranges::views::transform(BIND_BACK(ranges::views::transform, length_of_object))
            | ranges::views::transform(ranges::max_element);

    // Pad each cell to the correct length, join the cells with a pipe, and join the rows with newlines.
    auto formatted = table_data
            | ranges::views::transpose
            | ranges::views::transform([]<template <typename> typename C, typename U>(C<U>& column) {return column
                    | ranges::views::transform(fmt::formatter<U>::format)
                    | ranges::views::transform(BIND_BACK(pad_string, max_lengths | ranges::views::take(0)));}) // TODO : remove 0th element from max_lengths
            | ranges::views::transpose
            | ranges::views::transform(BIND_BACK(ranges::views::join, '|'))
            | ranges::views::join('\n');

    // Log this table row by row.
    ext::apply(
            [](auto&& table_rows) {detail::logger(detail::log_level_t::LOG, std::move(table_rows));},
            ext::make_tuple(std::move(formatted)));

}


template <typename ...Args>
auto console::console::trace(Args&& ...data) -> void
{
    auto* isolate = v8::Isolate::GetCurrent();
    auto trace = v8pp::from_v8<ext::vector<ext::string>>(isolate, v8::StackTrace::CurrentStackTrace(isolate, 10));
    auto formatted_data = detail::formatter(std::forward<Args>(data)...);
    trace.template emplace_front(formatted_data);
    ext::apply(BIND_FRONT(detail::printer, detail::print_type_t::TRACE), ext::make_tuple(std::move(trace)));
}


template <typename T>
auto console::console::dir(ext::any&& item, T&& options) -> void
{
    detail::printer(detail::print_type_t::DIR, ext::vector<ext::any>{std::move(item)}, std::forward<T>(options));
}


auto console::console::count(ext::string&& label) -> void
{
    ACCESS_PIMPL(console);
    d->count_map[label] += 1; // If doesn't exists -> becomes 0, then incrmenets to 1

    auto concat = label + char8_t(0x003a) + char8_t(0x0020) + ext::to_string(d->count_map.at(std::move(label)));
    detail::logger(detail::count_type_t::COUNT, concat);
}


auto console::console::count_reset(ext::string&& label) -> void
{
    ACCESS_PIMPL(console);
    d->count_map.insert_or_assign(std::move(label), 0);
}


template <typename ...Args>
auto console::console::group(Args&& ...data) -> void
{
    ACCESS_PIMPL(console);

    decltype(auto) group = std::make_unique<detail::group_t>();
    group->label = detail::formatter(std::forward<Args>(data)...);
    detail::printer(detail::group_type_t::GROUP, std::move(group));
    d->group_stack.push(std::move(group));
}


template <typename ...Args>
auto console::console::group_collapsed(Args&& ...data) -> void
{
    ACCESS_PIMPL(console);

    decltype(auto) group = std::make_unique<detail::group_t>();
    group->label = detail::formatter(std::forward<Args>(data)...);
    detail::printer(detail::group_type_t::GROUP_COLLAPSED, std::move(group));
    d->group_stack.push(std::move(group));
}


auto console::console::group_end()
{
    ACCESS_PIMPL(console);
    d->group_stack.pop();
}


auto console::console::time(ext::string&& label) -> void
{
    ACCESS_PIMPL(console);
    auto e = js::env::env::relevant(this);

    return_if (d->timer_table.contains(label));
    d->timer_table.insert(std::move(label), hr_time::detail::current_hr_time(e.js.global()));
}


template <typename ...Args>
auto console::console::time_log(ext::string&& label, Args&& ...data) -> void
{
    ACCESS_PIMPL(console);
    auto e = js::env::env::relevant(this);

    auto start_time = d->timer_table[label];
    auto duration = hr_time::detail::current_hr_time(e.js.global()) - start_time;
    auto concat = std::move(label) + char8_t(0x003a) + char8_t(0x0020) + ext::to_string(duration);
    detail::printer(detail::timer_type_t::TIME_LOG, std::move(concat), std::forward<Args>(data)...);
}


auto console::console::time_end(ext::string&& label) -> void
{
    ACCESS_PIMPL(console);
    auto e = js::env::env::relevant(this);

    auto start_time = d->timer_table |= ranges::actions::remove_key(std::move(label), ext::identity);
    auto duration = hr_time::detail::current_hr_time(e.js.global()) - start_time;
    auto concat = std::move(label) + char8_t(0x003a) + char8_t(0x0020) + ext::to_string(duration);
    detail::printer(detail::timer_type_t::TIME_END, std::move(concat));
}
