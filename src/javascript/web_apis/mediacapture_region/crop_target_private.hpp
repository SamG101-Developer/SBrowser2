#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/memory.hpp"
namespace dom::nodes {class element;}


DEFINE_PRIVATE_CLASS(mediacapture::region, crop_target) : virtual dom_object_private
{
    std::observer_ptr<dom::nodes::element> element;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_CROP_TARGET_PRIVATE_HPP