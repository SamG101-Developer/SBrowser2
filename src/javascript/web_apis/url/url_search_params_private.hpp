#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
#include "ext/map_like.hpp"

#include "ext/map.hpp"
#include "ext/string.hpp"
namespace url {class url;}


DEFINE_PRIVATE_CLASS(url, url_search_params)
        : virtual dom_object_private
        , ext::map_like_linked_private<ext::string, ext::string>
{
    MAKE_QIMPL(url_search_params);

    ext::multi_map<ext::string, ext::string> list;
    std::observer_ptr<url> url;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_SEARCH_PARAMS_PRIVATE_HPP
