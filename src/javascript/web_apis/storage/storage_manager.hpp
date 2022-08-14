#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_HPP

#include "dom_object.hpp"
namespace storage {class storage_manager;}

#include <future>
#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/string.hpp"

class storage::storage_manager
        : public virtual dom_object
{
public aliases:
    using storage_estimate_t = ext::map<ext::string, ext::number<ulonglong>>;

public js_methods:
    auto persisted() -> std::promise<ext::boolean>;
    auto persist() -> std::promise<ext::boolean>;
    auto estimate() -> std::promise<storage_estimate_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_HPP
