#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(web_locks)


DEFINE_PRIVATE_CLASS(web_locks, lock)
        : virtual dom_object_private
{
    MAKE_QIMPL(lock);

    std::unique_ptr<detail::lock_t> lock;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_PRIVATE_HPP
