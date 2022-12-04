#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MESSAGE_DATA_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MESSAGE_DATA_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"




DEFINE_PRIVATE_CLASS(push_api, push_message_data) : virtual dom_object_private
{
    ext::string bytes;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MESSAGE_DATA_PRIVATE_HPP
