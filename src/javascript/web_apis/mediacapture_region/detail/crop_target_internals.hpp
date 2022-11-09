#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_DETAIL_CROP_TARGET_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_DETAIL_CROP_TARGET_INTERNALS_HPP

#include <memory>
namespace dom::nodes {class element;}
namespace mediacapture::region {class crop_target;}

namespace mediacapture::detail
{
    auto create_crop_target(
            dom::nodes::element* element)
            -> std::unique_ptr<region::crop_target>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_REGION_DETAIL_CROP_TARGET_INTERNALS_HPP
