#ifndef SBROWSER2_WORKER_NAVIGATOR_HPP
#define SBROWSER2_WORKER_NAVIGATOR_HPP

#include "dom_object.hpp"
#include "badging/mixins/navigator_badge.hpp"
#include "device_memory/mixins/navigator_device_memory.hpp"
#include "storage/mixins/navigator_storage.hpp"
namespace html::other {class worker_navigator;}

namespace media::capabilities {class media_capabilities;}
namespace permissions {class permission;}
namespace service_workers::workers {class service_worker_container;}


class html::other::worker_navigator
        : public virtual dom_object
        , public badging::mixins::navigator_badge
        , public device_memory::mixins::navigator_device_memory
        , public storage::mixins::navigator_storage
{
public js_properties:
    /* PERMISSIONS */
    ext::property<permissions::permission*> permissions;

    /* MEDIA_CAPABILITIES */
    ext::property<std::unique_ptr<media::capabilities::media_capabilities>> media_capabilities;

    /* SERVICE_WORKERS */
    ext::property<std::unique_ptr<service_workers::workers::service_worker_container>> service_worker;
};

#endif //SBROWSER2_WORKER_NAVIGATOR_HPP
