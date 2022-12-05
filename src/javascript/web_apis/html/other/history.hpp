#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_HPP

// Inheritance Includes & This Class

namespace html::other {class history;}
namespace html::other {class history_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(html)


class html::other::history
        : public dom_object
{
public constructors:
    history();
    MAKE_PIMPL(history);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto go(ext::number<long> delta = 0) -> void;
    auto back() -> void;
    auto forward() -> void;
    auto push_state(ext::any&& data, ext::string_view unused, ext::string_view url = u8"") -> void;
    auto replace_state(ext::any&& delta, ext::string_view unused, ext::string_view url = u8"") -> void;

public js_properties:
    DEFINE_GETTER(length, ext::number<ulong>);
    DEFINE_GETTER(scroll_resotration, detail::scroll_restoration_t);
    DEFINE_GETTER(state, ext::any);

    DEFINE_SETTER(scroll_resotration, detail::scroll_restoration_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_HPP
