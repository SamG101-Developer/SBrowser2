#ifndef SBROWSER2_SHADOW_ROOT_HPP
#define SBROWSER2_SHADOW_ROOT_HPP

#include <web_apis/dom/nodes/document_fragment.hpp>
#include <web_apis/dom/mixins/document_or_shadow_root.hpp>
namespace dom::nodes {class shadow_root;}

namespace dom::nodes {class element;}


class dom::nodes::shadow_root final
        : public document_fragment
        , public mixins::document_or_shadow_root
{
public constructors:
    shadow_root();

public js_properties:
    ext::property<std::unique_ptr<element>> host;
    ext::property<ext::string> mode;
    ext::property<ext::string> slot_assignment;
    ext::property<ext::boolean> delegates_focus;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_methods:
    auto get_the_parent(events::event* event) -> event_target* override;

private cpp_properties:
    ext::boolean m_available_to_element_internals;
};


#endif //SBROWSER2_SHADOW_ROOT_HPP
