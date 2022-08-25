#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DETAIL_CHANGE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DETAIL_CHANGE_INTERNALS_HPP


namespace device_posture::detail
{
    auto update_device_posture()
            -> void;

    auto change()
            -> void;

    auto when_document_visible()
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_POSTURE_DETAIL_CHANGE_INTERNALS_HPP
