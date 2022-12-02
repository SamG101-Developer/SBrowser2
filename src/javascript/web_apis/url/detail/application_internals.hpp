#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_APPLICATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_APPLICATION_INTERNALS_HPP

#include "ext/map.ixx"
#include "ext/pair.ixx"
#include "ext/span.hpp"
#include "ext/string.hpp"

namespace encoding {class encoding;}


namespace url::detail
{
    auto application_x_www_form_urlencoded_parser(
            ext::string_view input)
            -> ext::map<ext::string, ext::string>;

    auto application_x_www_form_urlencoded_serializer(
            ext::map_span<ext::string, ext::string> tuples,
            encoding::encoding* encoding = nullptr)
            -> ext::string;

    auto application_x_www_form_urlencoded_string_parser(
            ext::string_view input)
            -> ext::map<ext::string, ext::string>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_URL_DETAIL_APPLICATION_INTERNALS_HPP
