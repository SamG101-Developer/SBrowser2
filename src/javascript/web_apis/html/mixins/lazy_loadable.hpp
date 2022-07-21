#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class lazy_loadable;}

class html::mixins::lazy_loadable
        : public virtual dom_object
{
public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

protected cpp_properties:
    ext::function<void()> m_lazy_load_resumption_steps;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_HPP
