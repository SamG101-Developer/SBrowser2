#ifndef SBROWSER2_SHADOW_ROOT_HPP
#define SBROWSER2_SHADOW_ROOT_HPP

#include <web_apis/dom/nodes/node.hpp>
namespace dom::nodes {class shadow_root;}


class dom::nodes::shadow_root
        : public node
{
public constructors:
    shadow_root();

public js_properties:
    ext::property<ext::string> mode;
    ext::property<ext::string> slot_assignment;
    ext::property<ext::boolean> delegates_focus;
};


#endif //SBROWSER2_SHADOW_ROOT_HPP
