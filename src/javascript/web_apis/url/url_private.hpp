#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(url)
namespace url {class url_search_params;}


DEFINE_PRIVATE_CLASS(url, url) : virtual dom_object_private
{
    MAKE_QIMPL(url);

    std::shared_ptr<detail::url_t> url;
    std::unique_ptr<url_search_params> query_object;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_URL_PRIVATE_HPP
