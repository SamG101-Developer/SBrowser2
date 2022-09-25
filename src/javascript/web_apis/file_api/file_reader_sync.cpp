#include "file_reader_sync.hpp"


file_api::file_reader_sync::file_reader_sync()
{
    INIT_PIMPL(file_reader_sync);
}


auto file_api::file_reader_sync::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<file_reader_sync>{isolate}
        .function("readAsArrayBuffer", &file_reader_sync::read_as_array_buffer)
        .function("readAsBinaryString", &file_reader_sync::read_as_array_buffer)
        .function("readAsText", &file_reader_sync::read_as_text)
        .function("readAsDataURL", &file_reader_sync::read_as_data_url)
        .auto_wrap_objects();

    return std::move(conversion);
}
