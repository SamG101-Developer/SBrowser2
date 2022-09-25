#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_HPP

#include "dom_object.hpp"
namespace mediacapture::region {class crop_target;}

#include "ext/promise.hpp"
namespace dom::nodes {class element;}


class mediacapture::region::crop_target
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(crop_target);
    crop_target() = default;

public js_methods:
    static auto from_element(dom::nodes::element) -> ext::promise<crop_target>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_HPP
