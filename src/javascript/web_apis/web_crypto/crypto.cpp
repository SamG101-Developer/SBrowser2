#include "crypto.hpp"

#include "ext/bit.hpp"
#include "ext/random.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "dom/detail/exception_internals.hpp"

#include <v8-array-buffer.h>
#include <v8-context.h>
#include <v8-isolate.h>


auto web_crypto::crypto::get_random_values(
        v8::Local<v8::ArrayBufferView> array)
        -> v8::Local<v8::ArrayBufferView>
{
    dom::detail::throw_v8_exception<TYPE_MISMATCH_ERR>(
            [array]
            {
                return !(array->IsInt8Array() || array->IsUint8Array() || array->IsUint8ClampedArray()
                        || array->IsInt16Array() || array->IsUint16Array() || array->IsInt32Array()
                        || array->IsUint32Array() || array->IsBigInt64Array() || array->IsBigUint64Array());
            },
            "Invalid array type");

    dom::detail::throw_v8_exception<QUOTA_EXCEEDED_ERR>(
            [byte_length = array->ByteLength()] {return byte_length > 65536;},
            "Byte length of array must be <= 65536");

    for (auto i = 0; i < array->ByteLength(); ++i)
        array->Set(v8::Isolate::GetCurrent()->GetCurrentContext(), i, v8pp::to_v8(v8::Isolate::GetCurrent(), ext::random::get()));
}


auto web_crypto::crypto::random_uuid()
        -> ext::string
{
    auto bytes = ext::string{16};
    for (auto& value: bytes) value = char(ext::random::get());

    ext::set_bits(bytes[6], 0b0100, ext::where_t::MOST_SIGNIFICANT);
    ext::set_bits(bytes[8], 0b10  , ext::where_t::MOST_SIGNIFICANT);

    std::stringstream uuid;
    uuid << std::hex << bytes[0] << bytes[1] << bytes[2] << bytes[3] << "-";
    uuid << std::hex << bytes[4] << bytes[5] << "-";
    uuid << std::hex << bytes[6] << bytes[7] << "-";
    uuid << std::hex << bytes[8] << bytes[9] << "-";
    uuid << std::hex << bytes[10] << bytes[11] << bytes[12] << bytes[13] << bytes[14] << bytes[15];
}
