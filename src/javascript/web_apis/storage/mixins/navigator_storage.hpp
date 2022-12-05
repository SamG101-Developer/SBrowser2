#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_NAVIGATOR_STORAGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_NAVIGATOR_STORAGE_HPP


namespace storage::mixins {class navigator_storage;}
namespace storage::mixins {class navigator_storage_private;}

namespace storage {class storage_manager;}


class storage::mixins::navigator_storage
        : public virtual dom_object
{
public constructors:
    navigator_storage();
    MAKE_PIMPL(navigator_storage);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(storage, storage_manager*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_NAVIGATOR_STORAGE_HPP
