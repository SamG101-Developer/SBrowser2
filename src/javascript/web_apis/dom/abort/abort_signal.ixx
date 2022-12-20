module;
#include "ext/macros/constructors.hpp"
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"
#include <tl/optional.hpp>


export module apis.dom.abort_signal;
import apis.dom.event_target;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, abort_signal) final
        : public event_target
{
public friends:
    friend class dom::event_target;

public constructors:
    DOM_CTORS(abort_signal);
    MAKE_PIMPL(abort_signal);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    static auto abort(ext::optional<ext::any>&& reason = ext::nullopt) -> std::unique_ptr<abort_signal>;
    static auto timeout(ext::number<ulonglong> milliseconds) -> std::unique_ptr<abort_signal>;
    auto throw_if_aborted() -> void;

private js_properties:
    DEFINE_GETTER(aborted, ext::boolean);
    DEFINE_GETTER(reason, ext::any);
};
