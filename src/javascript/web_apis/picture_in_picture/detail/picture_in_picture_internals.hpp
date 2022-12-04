#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PICTURE_IN_PICTURE_DETAIL_PICTURE_IN_PICTURE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PICTURE_IN_PICTURE_DETAIL_PICTURE_IN_PICTURE_INTERNALS_HPP




namespace picture_in_picture::detail
{
    auto request_picture_in_picture(
            ext::boolean user_activation_required,
            ext::boolean playing_required)
            -> void;

    auto exit_picture_in_picture()
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PICTURE_IN_PICTURE_DETAIL_PICTURE_IN_PICTURE_INTERNALS_HPP
