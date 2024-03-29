module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>


export module apis.dom.abort_signal;
import apis.dom.event_target;


DEFINE_PUBLIC_CLASS(dom, abort_signal) final
        : public event_target
{
public friends:
    friend class dom::event_target;

public constructors:
    DOM_CTORS(abort_signal);
    MAKE_PIMPL(abort_signal);
    MAKE_V8_AVAILABLE(ALL);

private js_methods:
    static auto abort(ext::optional<ext::any>&& reason = ext::nullopt) -> std::unique_ptr<abort_signal>;
    static auto timeout(ext::number<ulonglong> milliseconds) -> std::unique_ptr<abort_signal>;
    auto throw_if_aborted() -> void;

private js_properties:
    DEFINE_GETTER(aborted, ext::boolean);
    DEFINE_GETTER(reason, ext::any);
};
