module;
#include "ext/macros/annotations.hpp"
#include "ext/macros.hpp"
#include "ext/macros/other.hpp"
#include "javascript/macros/expose.hpp"
#include <function2/function2.hpp>


export module apis.reporting.reporting_observer;
import apis.dom_object;

import apis.reporting.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(reporting, reporting_observer) final
        : public virtual dom_object
{
public typedefs:
    using reporting_observer_callback_t = ext::function<void(ext::span<ext::string>, reporting_observer*)>;
    using reporting_observer_options_t = ext::map<ext::string, ext::any>;

public constructors:
    reporting_observer(reporting_observer_callback_t&& callback, reporting_observer_options_t&& options = {});
    MAKE_PIMPL(reporting_observer);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);
    MAKE_STRINGIFIER;

public js_methods:
    auto observe() -> void;
    auto disconnect() -> void;
    auto take_records() -> ext::vector<report*>;
};
