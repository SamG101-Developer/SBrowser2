module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.file_api.file_reader_sync;
import apis._.dom_object;

import ext.array_buffer;
import ext.enums;
import ext.tuple;
import ext.string;

import js.env.module_type;

namespace file_api {class blob;}


DEFINE_PUBLIC_CLASS(file_api, file_reader_sync) final
        : public virtual dom_object
{
public constructors:
    file_reader_sync();
    MAKE_PIMPL(file_reader_sync);
    MAKE_V8_AVAILABLE(DEDICATED_WORKER | SHARED_WORKER);

public js_methods:
    auto read_as_array_buffer(blob* blob_object) -> v8::Local<v8::ArrayBuffer>;
    auto read_as_binary_string(blob* blob_object) -> ext::string;
    auto read_as_text(blob* blob_object, ext::string_view encoding) -> ext::string;
    auto read_as_data_url(blob* blob_object) -> ext::string;
};
