#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_MIXINS_NAVIGATOR_LOCKS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_MIXINS_NAVIGATOR_LOCKS_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

namespace web_locks {class lock_manager;}


DEFINE_PRIVATE_CLASS(web_locks::mixins, navigator_locks)
        : virtual dom_object_private
{
    MAKE_QIMPL(navigator_locks);

    std::unique_ptr<lock_manager> lock_manager;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_MIXINS_NAVIGATOR_LOCKS_PRIVATE_HPP
