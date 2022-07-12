#ifndef SBROWSER2_HEADERS_HPP
#define SBROWSER2_HEADERS_HPP


#include "dom_object.hpp"
#include "_typedefs.hpp"
namespace fetch {class headers;}


class fetch::headers
        : public virtual web_apis::dom_object
{
public constructors:
    headers(const headers_t& headers);

public js_methods:
    auto append(header_name_t name, header_value_t value) -> void;
    auto delete_(header_name_t) -> void;
    auto get(header_name_t name) -> header_value_t;
    auto set(header_name_t name, header_value_t value) -> void;

private cpp_properties:
    headers_t m_headers_list;
    header_guard_t m_headers_guard;
};

#endif //SBROWSER2_HEADERS_HPP
