#ifndef SBROWSER2_JAVASCRIPT_WEB_APIS_INDEXED_DB__TYPEDEFS_HPP
#define SBROWSER2_JAVASCRIPT_WEB_APIS_INDEXED_DB__TYPEDEFS_HPP


#include <bit>
#include <variant>

#include "ext/date.ixx"

#include "ext/string.hpp"

#include "ext/vector.hpp"

#include "dom/nodes/node.hpp"
#include "dom/events/event.hpp"
namespace indexed_db {class idb_object_store;}
namespace indexed_db {class idb_index;}


namespace indexed_db::detail
{
    using number_key_t = ext::number<double>;
    using date_key_t = ext::datetime;
    using string_key_t = ext::string;
    using binary_key_t = std::byte;
    using array_key_t = ext::vector<ext::any>;
    using any_key_t = ext::variant<date_key_t, string_key_t, binary_key_t, array_key_t>; // number_key_t causes untold clangd crashes for unknown reasons

    template <typename T>
    struct record_value {using type = void;};

    template <>
    struct record_value<number_key_t> {using type = ext::number<double>;};

    template <>
    struct record_value<date_key_t> {using type = ext::number<double>;};

    template <>
    struct record_value<string_key_t> {using type = ext::string;};

    template <>
    struct record_value<binary_key_t> {using type = ext::string;};

    template <>
    struct record_value<array_key_t> {using type = ext::vector<ext::any>;};

    template <typename T>
    using record_value_t = typename record_value<T>::type;

    enum class transaction_mode_t {READONLY, READ_WRITE, VERSION_CHANGE};
    enum class transaction_state_t {ACTIVE, INACTIVE, COMMITTING, FINISHED};
    enum class durability_hint_t {STRICT, RELAXED, DEFAULT};
    enum class cursor_direction_t {NEXT, NEXT_UNIQUE, PREV, PREV_UNIQUE};

    using database_name_t = ext::string;
    using database_version_t = ext::number<ulonglong>;
    using key_path_t = ext::vector<ext::string>;

    struct record_t;
    struct key_generator_t;
    struct connection_t;
    struct key_range_t;

    template <typename T>
    concept source_like_c = requires
    {
        requires type_is<T, indexed_db::idb_object_store*, indexed_db::idb_index*>;
        {T::m_records} -> std::same_as<ext::vector<record_t*>&>;
    };
}


struct indexed_db::detail::record_t
{
public constructors:
    ~record_t();

public cpp_operators:
    auto operator==(const record_t& other) const;
    auto operator<=>(const record_t& other) const -> int;

public cpp_properties:
    any_key_t key;
    ext::any value;
};


struct indexed_db::detail::key_generator_t
{
public cpp_properties:
    ext::number<long> current_number = 1;
};


struct indexed_db::detail::connection_t
        : protected dom::nodes::event_target
{
public constructors:
    ~connection_t() {close_pending_flag = true;}

public cpp_properties:
    ext::number<int> version;
    ext::boolean close_pending_flag;
    ext::set<idb_object_store*> object_store_set;

protected cpp_methods:
    auto get_the_parent(dom::events::event* event) -> dom::nodes::event_target* override {return nullptr;}
};


struct indexed_db::detail::key_range_t
{
    std::unique_ptr<record_t> lower_bound;
    std::unique_ptr<record_t> upper_bound;
    ext::boolean lower_open_flag;
    ext::boolean upper_open_flag;
};

#endif //SBROWSER2_JAVASCRIPT_WEB_APIS_INDEXED_DB__TYPEDEFS_HPP
