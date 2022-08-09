#ifndef SBROWSER2_NAVIGATOR_HPP
#define SBROWSER2_NAVIGATOR_HPP

#include "dom_object.hpp"
namespace html::other {class navigator;}
namespace mediacapture::main {class media_devices;}


class html::other::navigator
{
    /* MEDIACAPTURE_MAIN */
    ext::property<mediacapture::main::media_devices*> media_devices;

};

#endif //SBROWSER2_NAVIGATOR_HPP
