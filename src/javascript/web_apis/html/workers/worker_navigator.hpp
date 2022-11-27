#ifndef SBROWSER2_WORKER_NAVIGATOR_HPP
#define SBROWSER2_WORKER_NAVIGATOR_HPP

#include "dom_object.hpp"
#include "html/navigators/mixins/navigator_id.hpp"
#include "html/navigators/mixins/navigator_language.hpp"
#include "html/navigators/mixins/navigator_on_line.hpp"
#include "html/navigators/mixins/navigator_concurrent_hardware.hpp"
#include "badging/mixins/navigator_badge.hpp"
#include "device_memory/mixins/navigator_device_memory.hpp"
#include "storage/mixins/navigator_storage.hpp"
#include "web_locks/mixins/navigator_locks.hpp"
namespace html::workers {class worker_navigator;}
namespace html::workers {class worker_navigator_private;}

namespace media::capabilities {class media_capabilities;}
namespace permissions {class permission;}
namespace service_workers::workers {class service_worker_container;}


class html::workers::worker_navigator
        : public virtual dom_object
        , public html::navigators::mixins::navigator_id
        , public html::navigators::mixins::navigator_language
        , public html::navigators::mixins::navigator_on_line
        , public html::navigators::mixins::navigator_concurrent_hardware

        , public badging::mixins::navigator_badge
        , public device_memory::mixins::navigator_device_memory
        , public storage::mixins::navigator_storage
{
private js_properties:
    /* [PERMISSIONS] */
    DEFINE_GETTER(permissions, permissions::permission*);

    /* [MEDIA-CAPABILITIES] */
    DEFINE_GETTER(media_capabilities, media::capabilities::media_capabilities*);

    /* [SERVICE-WORKERS] */
    DEFINE_GETTER(service_worker, service_workers::workers::service_worker_container*);
};

#endif //SBROWSER2_WORKER_NAVIGATOR_HPP
