#include "crop_target_internals.hpp"

#include "dom/nodes/element.hpp"

#include "mediacapture_region/crop_target.hpp"
#include "mediacapture_region/crop_target_private.hpp"


auto mediacapture::detail::create_crop_target(
        dom::nodes::element* element)
        -> std::unique_ptr<region::crop_target>
{
    auto crop_target = std::make_unique<region::crop_target>();
    crop_target->d_func()->element = element; // TODO : weak reference (when element destoryed, so is this object)
    return crop_target;
}
