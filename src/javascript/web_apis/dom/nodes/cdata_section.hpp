#ifndef SBROWSER2_CDATA_SECTION_HPP
#define SBROWSER2_CDATA_SECTION_HPP

#include "dom/nodes/text.hpp"
namespace dom::nodes {class cdata_section;}


class dom::nodes::cdata_section final
        : public text
{
public constructors:
    cdata_section() = default;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_GETTER(node_type) override {return CDATA_SECTION_NODE;}
    DEFINE_GETTER(node_name) override {return "#cdata-section";};
};


#endif //SBROWSER2_CDATA_SECTION_HPP
