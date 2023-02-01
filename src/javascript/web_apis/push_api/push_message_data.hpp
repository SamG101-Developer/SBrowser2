#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MESSAGE_DATA_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MESSAGE_DATA_HPP

// Inheritance Includes & This Class

namespace push_api {class push_message_data;}
namespace push_api {class push_message_data_private;}

// Other Includes & Forward Declarations


class push_api::push_message_data
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(push_message_data);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto array_buffer() const -> v8::Local<v8::ArrayBuffer>;
    auto blob() const -> file_api::blob;
    auto json() const -> ext::any;
    auto text() const -> ext::string_view;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MESSAGE_DATA_HPP
