#pragma once
#ifndef SBROWSER2_XPATH_NS_RESOLVER_HPP
#define SBROWSER2_XPATH_NS_RESOLVER_HPP

#include "dom_object.hpp"
namespace dom::xpath {class xpath_ns_resolver;}


class dom::xpath::xpath_ns_resolver
        : public virtual web_apis::dom_object
{
public js_methods:
    auto lookup_namespace_uri(ext::string_view prefix = "") -> ext::string;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_XPATH_NS_RESOLVER_HPP
