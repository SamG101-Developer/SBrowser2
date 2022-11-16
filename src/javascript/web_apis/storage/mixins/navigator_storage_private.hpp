#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_MIXINS_NAVIGATOR_STORAGE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_MIXINS_NAVIGATOR_STORAGE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

namespace storage {class storage_manager;}


DEFINE_PRIVATE_CLASS(storage::mixins, navigator_storage) : dom_object_private
{
    MAKE_QIMPL(navigator_storage);

    std::unique_ptr<storage_manager> storage;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_MIXINS_NAVIGATOR_STORAGE_PRIVATE_HPP
