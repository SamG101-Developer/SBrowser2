#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_COWL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_COWL_INTERNALS_HPP

#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(webappsec_cowl)

namespace webappsec::cowl {class label;}


namespace webappsec::detail
{
    auto is_principal(
            const principal_t& principle)
            -> ext::boolean;

    auto is_origin_principle(
            const principal_t& principle)
            -> ext::boolean;

    auto is_unique_principle(
            const principal_t& principle)
            -> ext::boolean;

    auto is_application_principle(
            const principal_t& principle)
            -> ext::boolean;

    auto is_label_in_normal_form(
            cowl::label* label)
            -> ext::boolean;

    auto are_labels_equivalent(
            cowl::label* label_a,
            cowl::label* label_b)
            -> ext::boolean;

    auto label_subsumes(
            cowl::label* label_a,
            cowl::label* label_b)
            -> ext::boolean;

    auto current_confidentially_label(

            );

    auto current_integrity_label(

            );
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_COWL_INTERNALS_HPP
