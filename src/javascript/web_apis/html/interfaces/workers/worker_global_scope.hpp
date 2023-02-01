#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP


#include "html/mixins/window_or_worker_global_scope.hpp"
namespace html::workers {class worker_global_scope;}
namespace html::workers {class worker_global_scope_private;}

namespace html::workers {class worker_location;}
namespace html::workers {class worker_navigator;}


class html::workers::worker_global_scope
        : public dom::nodes::event_target
        , public html::mixins::window_or_worker_global_scope
{
public constructors:
    DOM_CTORS(worker_global_scope);
    MAKE_PIMPL(worker_global_scope);
    MAKE_V8_AVAILABLE;

private js_methods:
    template <ext::type_is<ext::string>... Args> auto import_scripts(Args... urls);

private js_properties:
    DEFINE_GETTER(self, worker_global_scope*);
    DEFINE_GETTER(location, worker_location*);
    DEFINE_GETTER(navigator, worker_navigator*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_WORKERS_WORKER_GLOBAL_SCOPE_HPP
