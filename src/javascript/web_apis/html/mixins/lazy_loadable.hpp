#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class lazy_loadable;}
namespace html::mixins {class lazy_loadable_private;}


class html::mixins::lazy_loadable
        : public virtual dom_object
{
public constructors:
    lazy_loadable();
    MAKE_PIMPL(lazy_loadable);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_HPP
