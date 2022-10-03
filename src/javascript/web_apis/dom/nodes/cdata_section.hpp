#ifndef SBROWSER2_CDATA_SECTION_HPP
#define SBROWSER2_CDATA_SECTION_HPP

#include "dom/nodes/text.hpp"
namespace dom::nodes {class cdata_section;}

#include "dom/nodes/cdata_section_private.hpp"


class dom::nodes::cdata_section final
        : public text
{
public constructors:
    cdata_section();
    MAKE_PIMPL(cdata_section);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return CDATA_SECTION_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
};


#endif //SBROWSER2_CDATA_SECTION_HPP
