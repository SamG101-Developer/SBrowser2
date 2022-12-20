module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.range;
import apis.dom.abstract_range;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, range) final
        : public abstract_range
{
public friends:
    friend class dom::node;
    friend class dom::character_data_private;

public constructors:
    range();
    MAKE_PIMPL(range);
    MAKE_V8_AVAILABLE(WINDOW);
    MAKE_STRINGIFIER;

public js_static_constants:
    constexpr static const ext::number<short> START_TO_START = 0;
    constexpr static const ext::number<short> START_TO_END = 1;
    constexpr static const ext::number<short> END_TO_END = 2;
    constexpr static const ext::number<short> END_TO_START = 3;

public js_methods:
    auto set_start(node* new_container, ext::number<ulong> new_offset) -> void;
    auto set_start_before(node* new_container) -> void;
    auto set_start_after(node* new_container) -> void;

    auto set_end(node* new_container, ext::number<ulong> new_offset) -> void;
    auto set_end_before(node* new_container) -> void;
    auto set_end_after(node* new_container) -> void;

    auto insert_node(node* new_container) -> node*;
    auto intersects_node(node* container) const -> ext::boolean;
    auto select_node(node* container) -> void;
    auto select_node_contents(node* container) -> void;

    auto compare_boundary_points(ext::number<ushort> how, range* source_range) -> ext::number<short>;
    auto compare_point(node* container, ext::number<ulong> offset) const -> ext::number<short>;
    auto is_point_in_range(node* container, ext::number<ulong> offset) const -> ext::boolean;

    auto extract_contents() -> std::unique_ptr<document_fragment>;
    auto clone_contents() -> std::unique_ptr<document_fragment>;
    auto delete_contents() -> void;
    auto surround_contents(node* parent) -> std::unique_ptr<document_fragment>;

    auto collapse(ext::boolean  to_start = false) -> void;
    auto clone_range() const -> std::unique_ptr<range>;

    /* [DOM-PARSING] */
    auto create_contextual_fragmnt(ext::string&& fragment) -> std::unique_ptr<document_fragment>;

private js_properties:
    DEFINE_GETTER(common_ancestor_container, node*);
};
