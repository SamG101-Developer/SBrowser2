#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_WORKER_NAVIGATOR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_WORKER_NAVIGATOR_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
#include "html/navigators/mixins/navigator_id_private.hpp"
#include "html/navigators/mixins/navigator_language_private.hpp"
#include "html/navigators/mixins/navigator_on_line_private.hpp"
#include "html/navigators/mixins/navigator_concurrent_hardware_private.hpp"
#include "badging/mixins/navigator_badge_private.hpp"
#include "device_memory/mixins/navigator_device_memory_private.hpp"
#include "storage/mixins/navigator_storage_private.hpp"


DEFINE_PRIVATE_CLASS(html::workers, worker_navigator)
        : virtual dom_object_private
        , public html::navigators::mixins::navigator_id_private
        , public html::navigators::mixins::navigator_language_private
        , public html::navigators::mixins::navigator_on_line_private
        , public html::navigators::mixins::navigator_concurrent_hardware_private

        , public badging::mixins::navigator_badge_private
        , public device_memory::mixins::navigator_device_memory_private
        , public storage::mixins::navigator_storage_private
        , public web_locks::mixins::navigator_locks
{};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_WORKER_NAVIGATOR_PRIVATE_HPP
