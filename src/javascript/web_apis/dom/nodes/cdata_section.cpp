#include "cdata_section.hpp"
#include "cdata_section_private.hpp"

#include "dom/detail/customization_internals.hpp"


dom::nodes::character_data::character_data()
{
    INIT_PIMPL(character_data);
}


auto dom::nodes::cdata_section::get_node_name() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        return "#cdata-section";
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::cdata_section::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<cdata_section>{isolate}
        .inherit<text>()
        .auto_wrap_objects();

    return std::move(conversion);
}
