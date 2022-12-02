#pragma once
#include "html/detail/origin_internals.hpp"
#include "webappsec_cowl/privilege.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_COWL_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_COWL_INTERNALS_HPP

#include "ext/boolean.ixx"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(webappsec_cowl)

namespace webappsec::cowl {class label;}
namespace webappsec::cowl {class privilege;}


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

    auto origin_principal(
            const html::detail::origin_t& origin)
            -> ext::string;

    auto unique_principal()
            -> ext::string;

    auto application_specific_principal()
            -> ext::string;

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
            js::env::env& environment)
            -> cowl::label*;

    auto current_integrity_label(
            js::env::env& environment)
            -> cowl::label*;

    auto is_empty_label(
            cowl::label* label)
            -> ext::boolean;

    auto is_empty_pivilege(
            cowl::privilege* privilege)
            -> ext::boolean;

    auto is_unprivileged(
            const html::detail::browsing_context_t& context)
            -> ext::boolean;

    auto drop_privileges(
            const html::detail::browsing_context_t& context)
            -> ext::boolean;

    auto is_delegated_privilege_of(
            cowl::privilege* privilege_1,
            cowl::privilege* privilege_2)
            -> ext::boolean;

    auto default_cowl_state(
            const html::detail::origin_t& origin)
            -> std::unique_ptr<cowl_state_t>;
};


struct webappsec::detail::cowl_state_t
{
    ext::boolean confinement_mode;
    struct
    {
        ext::string context_confidentiality_label;
        ext::string context_integrity_label;
    } context_labels; // TODO : formatting

    std::unique_ptr<cowl::privilege> context_privilege;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_COWL_INTERNALS_HPP
