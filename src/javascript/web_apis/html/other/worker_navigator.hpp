#ifndef SBROWSER2_WORKER_NAVIGATOR_HPP
#define SBROWSER2_WORKER_NAVIGATOR_HPP

#include "dom_object.hpp"
#include "storage/mixins/navigator_storage.hpp"
namespace html::other {class worker_navigator;}

namespace media::capabilities {class media_capabilities;}
namespace permissions {class permission;}


class html::other::worker_navigator
        : public virtual dom_object
        , public storage::mixins::navigator_storage
{
    /* PERMISSIONS */
    ext::property<permissions::permission*> permissions;

    /* MEDIA_CAPABILITIES */
    ext::property<std::unique_ptr<media::capabilities::media_capabilities>> media_capabilities;
};

#endif //SBROWSER2_WORKER_NAVIGATOR_HPP
