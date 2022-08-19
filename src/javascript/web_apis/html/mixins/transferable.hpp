#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_TRANSFERABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_TRANSFERABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class transferable;}


class html::mixins::transferable
        : public virtual dom_object
{
protected cpp_methods:
    virtual auto transfer_steps() -> void = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_TRANSFERABLE_HPP
