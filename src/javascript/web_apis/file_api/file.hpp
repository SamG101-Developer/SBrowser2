#ifndef SBROWSER2_FILE_HPP
#define SBROWSER2_FILE_HPP

#include "blob.hpp"
namespace file_api {class file;}

#include INCLUDE_INNER_TYPES(file_api)

#include "file_private.hpp"


class file_api::file
        : public blob
{
public constructors:
    file(ext::vector<detail::blob_part_t>&& file_bits, ext::string&& file_name, detail::file_property_bag_t&& options = {});
    MAKE_PIMPL(file);
    MAKE_V8_AVAILABLE;
    MAKE_SERIALIZABLE;

private js_properties:
    DEFINE_GETTER(name, ext::string);
    DEFINE_GETTER(last_modified, ext::number<longlong>);
};


#endif //SBROWSER2_FILE_HPP
