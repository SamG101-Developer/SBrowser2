#ifndef SBROWSER2_HEADERS_HPP
#define SBROWSER2_HEADERS_HPP


#include "ext/map_like.ixx"
namespace fetch {class headers;}
namespace fetch {class headers_private;}

#include INCLUDE_INNER_TYPES(fetch)


class fetch::headers
        : public virtual dom_object
        , ext::map_like<detail::header_name_t, detail::header_value_t>
{
public constructors:
    headers(detail::headers_t&& headers);
    MAKE_PIMPL(headers);
    MAKE_V8_AVAILABLE(WINDOW | WORKER)

    auto operator[](const detail::header_name_t& key) -> detail::header_value_t& = 0;
    auto operator[](const detail::header_name_t& key) const -> detail::header_value_t& {return (*this)[key];}

public js_methods:
    auto append(detail::header_name_t&& name, detail::header_value_t&& value) -> void;
    auto delete_(ext::u8string_view name) -> void;
    auto get(ext::u8string_view name) -> detail::header_value_t; // TODO u8string?
    auto has(ext::u8string_view name) -> ext::boolean;
    auto set(detail::header_name_t&& name, detail::header_value_t&& value) -> void;
};

#endif //SBROWSER2_HEADERS_HPP
