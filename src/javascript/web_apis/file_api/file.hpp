#ifndef SBROWSER2_FILE_HPP
#define SBROWSER2_FILE_HPP


#include "blob.hpp"
namespace file_api {class file;}


class file_api::file
        : public blob
{
public constructors:
    file(ext::vector_view<blob_part_t> file_bits, ext::string_view file_name, ext::string_any_map_view options = {});

public js_properties:
    ext::property<ext::string> name;
    ext::property<ext::number<longlong>> last_modified;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_FILE_HPP
