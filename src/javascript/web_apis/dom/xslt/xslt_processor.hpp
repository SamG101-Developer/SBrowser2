#pragma once
#ifndef SBROWSER2_XSLT_PROCESSOR_HPP
#define SBROWSER2_XSLT_PROCESSOR_HPP

#include "dom_object.hpp"
namespace dom::xslt {class xslt_processor;}

namespace dom::nodes {class document_fragment;}


class dom::xslt::xslt_processor
        : public virtual dom_object
{
public constructors:
    xslt_processor();

public js_properties:
    auto import_stylesheet(nodes::node* style) -> void;
    auto transform_to_fragment(nodes::node* source, nodes::document* output) -> nodes::document_fragment*;
    auto transform_to_document(nodes::node* source) -> nodes::document*;

    auto get_parameter(ext::string_view namespace_, ext::string_view local_name) -> ext::any;
    auto set_parameter(ext::string_view namespace_, ext::string_view local_name, ext::any_view value) -> void;
    auto remove_parameter(ext::string_view namespace_, ext::string_view local_name) -> void;
    auto clear_parameters() -> void;
    auto reset() -> void;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_XSLT_PROCESSOR_HPP
