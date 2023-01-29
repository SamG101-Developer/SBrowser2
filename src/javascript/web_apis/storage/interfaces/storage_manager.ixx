module;
#include "ext/macros.hpp"


export module apis.storage.storage_manager;
import apis.dom_object;

import apis.storage.types;
import ext.js;


DEFINE_PUBLIC_CLASS(storage, storage_manager) final
        : virtual public dom_object
{
public constructors:
    storage_manager();
    MAKE_PIMPL(storage_manager);
    MAKE_V8_AVAILABLE(SECURE | WINDOW | WORKER);

public js_methods:
    auto persisted() -> ext::promise<ext::boolean>;
    auto persist() -> ext::promise<ext::boolean>;
    auto estimate() -> ext::promise<detail::storage_estimate_t>;
};
