#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_HPP

#include "dom_object.hpp"
namespace webappsec::cowl {class label;}

#include "ext/set.hpp"
#include INCLUDE_INNER_TYPES(webappsec_cowl)
namespace webappsec::cowl {class privelege;}


class webappsec::cowl::label
        : public virtual dom_object
{
public constructors:
    label() = default;
    label(detail::principal_t&& principal);

public js_methods:
    auto equals(label* other) -> ext::boolean;
    auto subsumes(label* other, privelege* priv = nullptr) -> ext::boolean;
    auto and_(ext::variant<label*, ext::string> other) -> label;
    auto or_(ext::variant<label*, ext::string> other) -> label;

public cpp_methods:
    auto to_json() const -> ext::string override;
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::set<detail::disjunction_set_t> m_label_set;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_HPP
