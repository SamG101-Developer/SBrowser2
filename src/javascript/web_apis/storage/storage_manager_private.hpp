#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(storage, storage_manager) : virtual dom_object_private
{
    MAKE_QIMPL(storage_manager);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_STORAGE_MANAGER_PRIVATE_HPP
