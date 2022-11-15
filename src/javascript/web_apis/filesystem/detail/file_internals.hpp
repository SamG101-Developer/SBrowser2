#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_DETAIL_FILE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_DETAIL_FILE_INTERNALS_HPP

#include "ext/memory.hpp"
#include "ext/promise.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(filesystem)
#include INCLUDE_INNER_TYPES(permissions)


namespace filesystem::detail
{
    auto is_valid_file_name(
            ext::string_view string)
            -> ext::boolean;

    auto take_lock(
            take_lock_t value,
            file_entry_t& file)
            -> ext::boolean;

    auto release_lock(
            file_entry_t& file)
            -> void;

    auto resolve_entry(
            entry_t& child,
            directory_entry_t& root)
            -> ext::promise<ext::vector<ext::string>>;
}


struct filesystem::detail::entry_t
{
    ext::string name;
    ext::function<permissions::detail::permission_state_t(mode_t)> query_access   = [](mode_t) {return permissions::detail::permission_state_t::DENIED;};
    ext::function<permissions::detail::permission_state_t(mode_t)> request_access = [](mode_t) {return permissions::detail::permission_state_t::DENIED;};

    auto operator==(const entry_t&) const -> ext::boolean;
    virtual ~entry_t();
};


struct filesystem::detail::file_entry_t : entry_t
{
    ext::u8string binary_data;
    ext::number<double> modification_timestamp;
    lock_t lock;
    ext::number<int> shared_lock_count;
};


struct filesystem::detail::directory_entry_t : entry_t
{
    ext::set<std::unique_ptr<entry_t>> children;
    std::observer_ptr<entry_t> parent;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILESYSTEM_DETAIL_FILE_INTERNALS_HPP
