#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_HPP

#include "dom_object.hpp"
namespace storage {class storage_manager;}
namespace storage {class storage_manager_private;}

#include "ext/promise.ixx"


#include "ext/map.ixx"

#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(storage)


class storage::storage_manager
        : virtual public dom_object
{
public constructors:
    storage_manager();
    MAKE_PIMPL(storage_manager);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto persisted() -> ext::promise<ext::boolean>;
    auto persist() -> ext::promise<ext::boolean>;
    auto estimate() -> ext::promise<detail::storage_estimate_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_HPP
