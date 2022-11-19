#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_HPP

#include "dom_object.hpp"
namespace webappsec::cowl {class label;}
namespace webappsec::cowl {class label_private;}

#include INCLUDE_INNER_TYPES(webappsec_cowl)
namespace webappsec::cowl {class privilege;}


class webappsec::cowl::label
        : public virtual dom_object
{
public constructors:
    MAKE_PIMPL(label);
    MAKE_STRINGIFIER;
    MAKE_V8_AVAILABLE;
    label(detail::principal_t&& principal = u"");

public js_methods:
    auto equals(label* other) -> ext::boolean;
    auto subsumes(label* other, privilege* priv = nullptr) -> ext::boolean;

    auto and_(label* other) const -> std::unique_ptr<label>;
    auto and_(ext::string&& other) const -> std::unique_ptr<label>;
    auto or_(label* other) const -> std::unique_ptr<label>;
    auto or_(ext::string&& other) const -> std::unique_ptr<label>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_HPP
