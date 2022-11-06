#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_HPP

#include "dom_object.hpp"
namespace html::workers {class worklet;}
namespace html::workers {class worklet_private;}

#include INCLUDE_INNER_TYPES(html)
#include "ext/promise.hpp"


class html::workers::worklet
        : public virtual dom_object
{
public constructors:
    worklet();
    MAKE_PIMPL(worklet);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto add_module(ext::string_view module_url, detail::worklet_options_t&& options = {}) -> ext::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_HPP
