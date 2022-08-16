#ifndef SBROWSER2_FILE_READER_SYNC_HPP
#define SBROWSER2_FILE_READER_SYNC_HPP


#include "dom_object.hpp"
namespace file_api {class file_reader_sync;}

namespace file_api {class blob;}


class file_api::file_reader_sync
        : public virtual dom_object
{
public constructors:
    file_reader_sync();

public js_methods:
    auto read_as_array_buffer(blob& blob_object) -> v8::Local<v8::ArrayBuffer>;
    auto read_as_binary_string(blob& blob_object) -> ext::string;
    auto read_as_text(blob& blob_object, ext::string_view encoding) -> ext::string;
    auto read_as_data_url(blob& blob_object) -> ext::string;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_FILE_READER_SYNC_HPP
