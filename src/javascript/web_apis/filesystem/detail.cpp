module apis.filesystem.detail;


auto filesystem::detail::is_valid_file_name(ext::string_view string) -> ext::boolean
{
    // TODO : remove std::... dependancy
    return !string.empty() && string != u"." && string != u".."
            && !ranges::contains(string, u"/")
            && !ranges::contains(string, std::filesystem::path::preferred_separator);
}


auto filesystem::detail::take_lock(take_lock_t value, file_entry_t& file) -> ext::boolean
{
    // Exclusive operations on an open lock result in the lock becoming taken exclusively. The lock isn't taken or
    // shared, so don't increment the 'shared_lock_count'. Acts like a unique_ptr<T>. Returning true signifies a
    // successful operation.
    if (value == take_lock_t::EXCLUSIVE && file.lock == lock_t::OPEN)
    {
        file.lock = lock_t::TAKEN_EXCLUSIVE;
        return true;
    }

    // Shared operations on an open lock result in the lock becoming taken shared. The lock isn't taken, so set the
    // 'shared_lock_count' to 1. Acts like a shared_ptr<T> with reference count 1. Returning true signifies a successful
    // operation.
    if (value == take_lock_t::SHARED && file.lock == lock_t::OPEN)
    {
        file.lock = lock_t::TAKEN_SHARED;
        file.shared_lock_count = 1;
        return true;
    }

    // Shared operations on a taken shared lock result in the lock staying the same state (still taken shared). As the
    // lock is taken, incrmene the 'shared_lock_count' by 1. Acts like a shared_ptr<T> incrmenting the reference count.
    // Returning true signifies a successful operation.
    if (value == take_lock_t::SHARED && file.lock == lock_t::TAKEN_SHARED)
    {
        file.shared_lock_count += 1;
        return true;
    }

    // If none of the other branches were chosen, then the taking of the lock is invalid, because of the current state
    // and type of operation. Returning false signifies a failed operation. Returning true signifies a successful
    // operation.
    return false;
}


auto filesystem::detail::release_lock(file_entry_t& file) -> void
{
    if (file.lock == lock_t::TAKEN_SHARED)
    {
        file.shared_lock_count -= 1;
        file.lock = file.shared_lock_count == 0 ? lock_t::OPEN : file.lock;
    }

    else
        file.lock = lock_t::OPEN;
}


auto filesystem::detail::resolve_entry(entry_t& child, directory_entry_t& root) -> ext::promise<ext::vector<ext::string>>
{
    auto result = ext::promise<ext::vector<ext::string>>{};
    auto e = js::env::env::relevant(result); // TODO : which env?

    GO [&e, &child, &root, &result]
    {
        return_if (child == root) web_idl::detail::resolve_promise(result, {});
        auto child_promises = ext::vector<ext::promise<ext::vector<ext::string>>>{};

        for (decltype(auto) entry: root.children | ranges::views::transform(&std::unique_ptr<entry_t>::get))
        {
            child_promises.emplace_back(resolve_entry(child, dom_cast<directory_entry_t&>(entry)));
            auto on_fulfillment =
                    [result](ext::vector<ext::string>& path)
                    {if (!path.empty()) web_idl::detail::resolve_promise(result, path);};

            web_idl::detail::upon_fulfillment(child_promises.back(), e.js.realm(), std::move(on_fulfillment));
        }
        web_idl::detail::wait_for_all(child_promises, e.js.realm(), [result] {if (!web_idl::detail::is_resolved(result));});
    };

    return result;
}
