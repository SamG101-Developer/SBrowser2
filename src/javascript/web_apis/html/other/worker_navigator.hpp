#ifndef SBROWSER2_WORKER_NAVIGATOR_HPP
#define SBROWSER2_WORKER_NAVIGATOR_HPP

#include "dom_object.hpp"
#include "storage/mixins/navigator_storage.hpp"
namespace html::other {class worker_navigator;}

namespace permissions {class permission;}


class html::other::worker_navigator
        : public virtual dom_object
        , public storage::mixins::navigator_storage
{
    /* PERMISSIONS */
    ext::property<permissions::permission*> permissions;
};

#endif //SBROWSER2_WORKER_NAVIGATOR_HPP
