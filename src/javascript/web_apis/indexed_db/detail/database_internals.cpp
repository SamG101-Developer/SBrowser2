#include "database_internals.hpp"

#include "ext/assertion.hpp"


#include "ext/type_traits.ixx"

"
#include "infra/detail/infra_strings_internals.hpp"

#include <range/v3/view/set_algorithm.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>


auto indexed_db::detail::database_internals::compare_two_keys(
        const record_t& a,
        const record_t& b)
        -> ext::number<short>
{
    // how to handle two records whose keys are different types (obviously their values can't be compared becuase they
    // are different types - auto casting might be unwanted behaviour for JavaScipt)
    if (ext::variant_type(a.key) != ext::variant_type(b.key))
    {
        return_if(ext::holds_alternative<array_key_t>(a.key)) 1;
        return_if(ext::holds_alternative<array_key_t>(b.key)) -1;

        return_if(ext::holds_alternative<binary_key_t>(a.key)) 1;
        return_if(ext::holds_alternative<binary_key_t>(b.key)) -1;

        return_if(ext::holds_alternative<string_key_t>(a.key)) 1;
        return_if(ext::holds_alternative<string_key_t>(b.key)) -1;

        return_if(ext::holds_alternative<date_key_t>(a.key)) 1;
        return_if(ext::holds_alternative<date_key_t>(b.key)) -1;

        ASSERT(false,
               "Type mismatch",
               ext::variant_type(a.key),
               ext::variant_type(b.key));
    }

    // copy the values from the records (saved for casting)
    auto va = a.value;
    auto vb = b.value;

    // TODO : return_if MACRO (mouse broken atm)
    // for two numbers: standard three-way number comparison using std::less to determine if the left < right or not.
    if (ext::holds_alternative<number_key_t>(a.key))
        return ext::three_way_compare(
                va.to<record_value_t<number_key_t>>(),
                vb.to<record_value_t<number_key_t>>());

    // for two dates: standard three-way number comparison using std::less to determine if the left < right or not - the
    // date is converted to its integer form (time since epoch) implicitly
    if (ext::holds_alternative<date_key_t>(a.key))
        return ext::three_way_compare(
                va.to<record_value_t<date_key_t>>(),
                vb.to<record_value_t<date_key_t>>());

    // for two strings: standard three-way number comparison using the Infra 'is_code_unit_less_than(...)' comparison
    // method
    if (ext::holds_alternative<string_key_t>(a.key))
        return ext::three_way_compare(
                va.to<record_value_t<string_key_t>>(),
                vb.to<record_value_t<string_key_t>>(),
                infra::detail::infra_string_internals::is_code_unit_less_than);

    // for two binaries: standard three-way number comparison using the Infra 'is_code_unit_less_than(...)' comparison
    // method
    if (ext::holds_alternative<binary_key_t>(a.key))
        return ext::three_way_compare(
                va.to<record_value_t<binary_key_t>>(),
                vb.to<record_value_t<binary_key_t>>(),
                infra::detail::infra_string_internals::is_code_unit_less_than);

    // final test for the type of key (ie this is the only type the key can be) - the array type
    if (ext::holds_alternative<array_key_t>(a.key))
    {
        // cast the ext::any values of the records to the ext::vector<ext::any> type, and zip them into 'zip' - so
        // zip.at(0) = ranges::common_pair{va.at(0), vb.at(0)}
        auto va_array = va.to<record_value_t<array_key_t>>();
        auto vb_array = vb.to<record_value_t<array_key_t>>();
        auto zip = ranges::views::zip(
                va_array,
                vb_array);

        // iterator through each pair in the zip, creating mock records with the key and the individual items in the
        // lists (the ext::any item of the ext::vector<ext::any> gets cast into the correct type in the recursive call).
        // if the returned value is 1 or -1, then it is returned, otherwise the return value is 0, signifying equal
        // values, so continue iteration of the items in the lists
        for (auto&& va_vb_values: zip)
        {
            auto result = compare_two_keys(
                    record_t{a.key, va_vb_values.first},
                    record_t{b.key, va_vb_values.second});
            return_if(result != 0) result;
        }

        // if all the items in the array are equal (limited to the size of the smallest list), then compare the sizes of
        // the lists to determine the "smaller" key
        return ext::three_way_compare(
                va_array.size(),
                vb_array.size());
    }
}


auto indexed_db::detail::database_internals::is_key_path_valid(
        ext::vector_view<ext::string> key_path)
        -> ext::boolean
{
    return key_path.size() == 0
            || key_path.size() == 1 // TODO
            || key_path.size() == 1 && is_key_path_valid(key_path.front() | ranges::views::split_string(0x002E)) // TODO
            || ranges::all_of(std::move(key_path), is_key_path_valid);
}


auto indexed_db::detail::database_internals::uses_in_line_keys(
        const object_store_t& object_store)
        -> ext::boolean
{
    // a 'object_store' that uses in-line keys will have a non-empty 'key_path' attribute
    return !object_store.key_path.empty();
}


auto indexed_db::detail::database_internals::uses_out_of_line_keys(
        const object_store_t& object_store)
        -> ext::boolean
{
    // a 'object_store' that uses out-of-line keys will have an empty 'key_path' attribute
    return object_store.key_path.empty();
}


auto indexed_db::detail::database_internals::transactions_have_overlapping_scope(
        const transaction_t& transaction_a,
        const transaction_t& transaction_b)
        -> ext::boolean
{
    return !ranges::views::set_intersection(
            transaction_a.scope,
            transaction_b.scope).empty();
}


auto indexed_db::detail::database_internals::key_range_containing_only(
        const key_range_t& key_range,
        const record_t& key)
        -> ext::boolean
{
    return *key_range.lower_bound == key && *key_range.upper_bound == key;
}


auto indexed_db::detail::database_internals::key_in_key_range(
        const key_range_t& key_range,
        const record_t& key)
        -> ext::boolean
{
    return !key_range.lower_bound
            || *key_range.lower_bound < key
            || *key_range.lower_bound == key && !key_range.lower_open_flag

            || !key_range.upper_bound
            || *key_range.upper_bound > key
            || *key_range.upper_bound == key && !key_range.upper_open_flag;
}


auto indexed_db::detail::database_internals::unbounded_key_range(
        const key_range_t& key_range)
        -> ext::boolean
{
    return !key_range.lower_bound && !key_range.upper_bound;
}


auto indexed_db::detail::database_internals::generate_key_for_object_store(
        object_store_t& object_store)
        -> ext::number<long>
{
    return object_store.m_generator.current_number > std::pow(2, 53)
            ? -1 // FAILURE
            : object_store.m_generator.current_number += 1;
}


auto indexed_db::detail::database_internals::possible_update_key_generator(
        object_store_t& object_store,
        const record_t& record)
        -> void
{
    return_if (!ext::holds_alternative<number_key_t>(object_store));

    auto value = ext::min(record.value.to<record_value_t<number_key_t>>(), std::pow(2L, 53L));
    object_store.m_generator.current_number = value > object_store.m_generator.current_number
            ? value + 1
            : object_store.m_generator.current_number;
}
