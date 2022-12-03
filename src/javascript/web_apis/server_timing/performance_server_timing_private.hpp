#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_PERFORMANCE_SERVER_TIMING_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_PERFORMANCE_SERVER_TIMING_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


#include "ext/map.ixx"
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(server_timing, performance_server_timing) : dom_object_private
{
    ext::string metric_name;
    ext::map<ext::string, ext::any> params;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVER_TIMING_PERFORMANCE_SERVER_TIMING_PRIVATE_HPP
