#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_DETAIL_EXTENSION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_DETAIL_EXTENSION_INTERNALS_HPP

#include <v8-forward.h>
#include "ext/set.hpp"


namespace badging::detail
{
    auto determine_matching_applications(
            v8::Local<v8::Object>)
            -> ext::set<app_manifest::detail::installed_web_application_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_DETAIL_EXTENSION_INTERNALS_HPP
