#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_MANAGER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(web_locks, lock_manager) : dom_object_private
{
    MAKE_QIMPL(lock_manager);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_MANAGER_PRIVATE_HPP
