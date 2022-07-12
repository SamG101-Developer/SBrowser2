#ifndef SBROWSER2_XHR_INTERNALS_HPP
#define SBROWSER2_XHR_INTERNALS_HPP

#include "ext/string.hpp"
namespace xhr {class xml_http_request;}

namespace xhr::detail::xhr_internals
{
    auto report_timing(
            xml_http_request& xhr_object)
            ->void;

    auto handle_response_end_of_body(
            xml_http_request& xhr_object)
            -> void;

    auto handle_errors(
            xml_http_request& xhr_object)
            -> void;

    auto request_error_steps(
            xml_http_request& xhr_object)
            -> void;

    auto get_response_mime_type(
            xml_http_request& xhr_object)
            -> ext::string;

    auto get_final_mime_type(
            xml_http_request& xhr_object)
            -> ext::string;

    auto get_final_encoding(
            xml_http_request& xhr_object)
            -> ext::string;

    auto set_document_response(
            xml_http_request& xhr_object)
            -> ext::string;
}

#endif //SBROWSER2_XHR_INTERNALS_HPP
