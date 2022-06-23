#ifndef SBROWSER2_SLOTTABLE_HPP
#define SBROWSER2_SLOTTABLE_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mixins {class slottable;}

namespace html::elements {class html_slot_element;}


class dom::mixins::slottable
        : public virtual web_apis::dom_object
{
public friends:
    friend class html::elements::html_slot_element;

public constructors:
    slottable();

public js_properties:
    ext::property<std::unique_ptr<html::elements::html_slot_element>> assigned_slot;

private cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_assigned_slot() const -> html::elements::html_slot_element*;
};


#endif //SBROWSER2_SLOTTABLE_HPP
