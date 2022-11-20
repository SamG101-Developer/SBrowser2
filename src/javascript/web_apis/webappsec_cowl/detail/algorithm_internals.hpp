#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
namespace webappsec::cowl {class label;}
namespace webappsec::cowl {class privilege;}


namespace webappsec::detail
{
    auto label_normal_form_reduction(
            cowl::label* label)
            -> cowl::label;

    auto label_subsumption(
            cowl::label* label_a,
            cowl::label* label_b)
            -> ext::boolean;

    auto label_downgrade(
            cowl::label* label,
            cowl::privilege* privilege)
            -> std::unique_ptr<cowl::label>;

    auto label_upgrade(
            cowl::label* label,
            cowl::privilege* privilege)
            -> std::unique_ptr<cowl::label>;

    auto context_tainting(
            cowl::label* confidentiality,
            cowl::label* integrity)
            -> void;

    auto write_check(
            cowl::label* confidentiality,
            cowl::label* integrity)
            -> ext::boolean;

    template <typename T>
    auto structured_clone(
            T* object)
            -> std::unique_ptr<T>;

    auto should_request_be_blocked_as_cowl(
            const fetch::detail::request_t& request)
            -> ext::boolean;

    auto process_response_to_request_as_cowl(
            const fetch::detail::request_t& request,
            const fetch::detail::response_t& response)
            -> ext::boolean; // TODO : change return type to allowed / blocked

    auto parse_labeled_data_metadata(
            const html::detail::origin_t& origin)
            -> ext::tuple<std::unique_ptr<cowl::label>, std::unique_ptr<cowl::label>>;

    auto parse_labeled_context_metadata(
            const html::detail::origin_t& origin)
            -> ext::tuple<std::unique_ptr<cowl::label>, std::unique_ptr<cowl::label>, std::unique_ptr<cowl::privilege>>;

    auto parse_label_expression(
            ext::string_view label_expression,
            ext::string_view url)
            -> std::unique_ptr<cowl::label>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_ALGORITHM_INTERNALS_HPP
