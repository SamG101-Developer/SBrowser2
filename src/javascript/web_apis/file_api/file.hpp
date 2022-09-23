#ifndef SBROWSER2_FILE_HPP
#define SBROWSER2_FILE_HPP

#include "blob.hpp"
namespace file_api {class file;}

#include INCLUDE_INNER_TYPES(file_api)


class file_api::file
        : public blob
{
public constructors:
    file(ext::vector<detail::blob_part_t>&& file_bits, ext::string&& file_name, detail::file_property_bag_t&& options = {});
    ~file() override = default;

private js_properties:
    ext::property<ext::string> name;
    ext::property<ext::number<longlong>> last_modified;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected cpp_methods:
    auto m_serialize  (ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> void override;
    auto m_deserialize(ext::map<ext::string, ext::any>& serialized, ext::boolean for_storage) -> file* override;
};


#endif //SBROWSER2_FILE_HPP
