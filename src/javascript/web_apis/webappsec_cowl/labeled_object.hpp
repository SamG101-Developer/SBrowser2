#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABELED_OBJECT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABELED_OBJECT_HPP

// Inheritance Includes & This Class

namespace webappsec::cowl {class labeled_object;}
namespace webappsec::cowl {class labeled_object_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(webappsec_cowl)
#include INCLUDE_CONCEPTS(html)
namespace webappsec::cowl {class label;}


class webappsec::cowl::labeled_object
        : virtual public dom_object
{
public constructors:
    template <html::concepts::is_serializable T>
    labeled_object(T* object, detail::ci_label_t&& labels = {});
    MAKE_PIMPL(labeled_object);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto clone(detail::ci_label_t&& labels) -> std::unique_ptr<labeled_object>;

public js_properties:
    DEFINE_GETTER(confidentiality, label*);
    DEFINE_GETTER(integrity, label*);
    DEFINE_GETTER(protected_object, void*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABELED_OBJECT_HPP
