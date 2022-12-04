#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_HPP

#include "dom_object.hpp"
namespace mediacapture::region {class crop_target;}
namespace mediacapture::region {class crop_target_private;}


namespace dom::nodes {class element;}


class mediacapture::region::crop_target
        : public virtual dom_object
{
public constructors:
    crop_target();
    MAKE_PIMPL(crop_target);
    MAKE_SERIALIZABLE;
    MAKE_V8_AVAILABLE;

public js_methods:
    static auto from_element(dom::nodes::element) -> ext::promise<crop_target>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_HPP
