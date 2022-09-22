#include "abstract_range.hpp"

#include "dom/detail/range_internals.hpp"


auto dom::node_ranges::abstract_range::get_start_container() const -> typename decltype(this->start_container)::value_t
{return d_ptr->start->node;}


auto dom::node_ranges::abstract_range::get_start_offset() const -> typename decltype(this->start_offset)::value_t
{return d_ptr->start->offset;}


auto dom::node_ranges::abstract_range::get_end_container() const -> typename decltype(this->end_container)::value_t
{return d_ptr->end->node;}


auto dom::node_ranges::abstract_range::get_end_offset() const -> typename decltype(this->end_offset)::value_t
{return d_ptr->end->offset;}


auto dom::node_ranges::abstract_range::get_collapsed() const -> typename decltype(this->collapsed)::value_t
{return detail::is_range_collapsed(this);}


auto dom::node_ranges::abstract_range::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<abstract_range>{isolate}
            .inherit<dom_object>()
            .var("collapsed", &abstract_range::collapsed, true)
            .var("startContainer", &abstract_range::start_container, true)
            .var("startOffset", &abstract_range::start_offset, true)
            .var("endContainer", &abstract_range::end_container, true)
            .var("endOffset", &abstract_range::end_offset, true)
            .auto_wrap_objects();

    return std::move(conversion);
}
