#ifndef SBROWSER2_HEADERS_HPP
#define SBROWSER2_HEADERS_HPP

#include "dom_object.hpp"
#include INCLUDE_INNER_TYPES(fetch)
namespace fetch {class headers;}


class fetch::headers
        : public virtual dom_object
{
public constructors:
    headers(const detail::headers_t& headers);

public js_methods:
    auto append(const detail::header_name_t& name, detail::header_value_t value) -> void;
    auto delete_(const detail::header_name_t& name) -> void;
    auto get(const detail::header_name_t& name) -> detail::header_value_t;
    auto set(const detail::header_name_t& name, detail::header_value_t value) -> void;

private cpp_properties:
    detail::headers_t m_headers_list;
    detail::header_guard_t m_headers_guard;
};

#endif //SBROWSER2_HEADERS_HPP
