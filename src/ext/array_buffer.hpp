#ifndef SBROWSER2_SRC_EXT_ARRAY_BUFFER_HPP
#define SBROWSER2_SRC_EXT_ARRAY_BUFFER_HPP

#include "ext/variant.hpp"
#include <v8-forward.h>


_EXT_BEGIN
    struct array_buffer {using v8_constructor = v8::ArrayBuffer;};
    struct array_buffer_view {using v8_constructor = v8::ArrayBufferView;};
    struct data_view : array_buffer_view {using v8_constructor = v8::DataView;};
    struct int8_array : array_buffer_view {using v8_constructor = v8::Int8Array;};
    struct int16_array : array_buffer_view {using v8_constructor = v8::Int16Array;};
    struct int32_array : array_buffer_view {using v8_constructor = v8::Int32Array;};
    struct uint8_array : array_buffer_view {using v8_constructor = v8::Uint8Array;};
    struct uint16_array : array_buffer_view {using v8_constructor = v8::Uint16Array;};
    struct uint32_array : array_buffer_view {using v8_constructor = v8::Uint32Array;};
    struct uint8_clamped_array : array_buffer_view {using v8_constructor = v8::Uint8ClampedArray;};
    struct bigint64_array : array_buffer_view {using v8_constructor = v8::BigInt64Array;};
    struct biguint64_array : array_buffer_view {using v8_constructor = v8::BigUint64Array;};
    struct float32_array : array_buffer_view {using v8_constructor = v8::Float32Array;};
    struct float64_array : array_buffer_view {using v8_constructor = v8::Float64Array;};
    using buffer_source = ext::variant<array_buffer, array_buffer_view>;
_EXT_END


#endif //SBROWSER2_SRC_EXT_ARRAY_BUFFER_HPP
