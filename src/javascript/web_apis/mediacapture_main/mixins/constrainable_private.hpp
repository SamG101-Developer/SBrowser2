#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MIXINS_CONSTRAINABLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MIXINS_CONSTRAINABLE_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(mediacapture_main)


DEFINE_PRIVATE_CLASS(mediacapture::main::mixins, constrainable) : virtual dom_object_private
{
    detail::capabilities_t capabilities;
    detail::constraints_t constraints;
    detail::settings_t settings;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MIXINS_CONSTRAINABLE_PRIVATE_HPP
