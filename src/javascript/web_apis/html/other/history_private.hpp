#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(html)


DEFINE_PRIVATE_CLASS(html::other, history) : dom_object_private
{
    ext::any state;
    ext::number<ulong> length;
    ext::number<ulong> index;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_PRIVATE_HPP
