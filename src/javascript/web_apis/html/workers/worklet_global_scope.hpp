#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_GLOBAL_SCOPE_HPP

#include "dom_object.hpp"
namespace html::workers {class worklet_global_scope;}
namespace html::workers {class worklet_global_scope_private;}


class html::workers::worklet_global_scope
        : public virtual dom_object
{
public constructors:
    worklet_global_scope();
    MAKE_PIMPL(worklet_global_scope);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKLET_GLOBAL_SCOPE_HPP
