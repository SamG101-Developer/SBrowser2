#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_NAVIGATOR_STORAGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_NAVIGATOR_STORAGE_HPP

#include "dom_object.hpp"
namespace storage::mixins {class navigator_storage;}

namespace storage {class storage_manager;}


class storage::mixins::navigator_storage
        : public virtual dom_object
{
public js_properties:
    ext::property<storage_manager*> storage;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STORAGE_NAVIGATOR_STORAGE_HPP
