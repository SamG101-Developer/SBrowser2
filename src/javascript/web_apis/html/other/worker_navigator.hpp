#ifndef SBROWSER2_WORKER_NAVIGATOR_HPP
#define SBROWSER2_WORKER_NAVIGATOR_HPP

#include "dom_object.hpp"
namespace html::other {class worker_navigator;}

namespace permissions {class permission;}


class html::other::worker_navigator
        : public virtual dom_object
{
    /* PERMISSIONS */
    ext::property<permissions::permission*> permissions;
};

#endif //SBROWSER2_WORKER_NAVIGATOR_HPP
